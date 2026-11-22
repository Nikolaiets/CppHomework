#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
constexpr bool is_inf_type_v =
    std::is_same_v<std::decay_t<T>, std::string> ||
    std::is_same_v<std::decay_t<T>, const char*>;

template <typename T>
double to_bound_double(const T& val, bool is_left) {
    if constexpr (is_inf_type_v<T>) {
        (void)val;
        return is_left ? -1e300 : 1e300;
    } else {
        return static_cast<double>(val);
    }
}

template <typename LeftT = double, typename RightT = double>
class Interval {
public:
    using Pair = std::pair<LeftT, RightT>;

    Interval(LeftT l, RightT r, bool l_inc = true, bool r_inc = true)
        : bounds_(std::move(l), std::move(r)),
          l_inc_(is_inf_type_v<LeftT> ? false : l_inc),
          r_inc_(is_inf_type_v<RightT> ? false : r_inc) {
        if constexpr (!is_inf_type_v<LeftT> && !is_inf_type_v<RightT>) {
            if (bounds_.first > bounds_.second ||
                (bounds_.first == bounds_.second && (!l_inc_ || !r_inc_))) {
                throw std::invalid_argument("Invalid or empty interval.");
            }
        }
    }

    explicit Interval(Pair p, bool l_inc = true, bool r_inc = true)
        : Interval(std::move(p.first), std::move(p.second), l_inc, r_inc) {}

    const Pair& bounds() const noexcept { return bounds_; }
    bool leftInclusive() const noexcept { return l_inc_; }
    bool rightInclusive() const noexcept { return r_inc_; }

    void print(std::ostream& os = std::cout) const {
        os << (l_inc_ ? '[' : '(');
        if constexpr (is_inf_type_v<LeftT>) os << "-inf";
        else os << bounds_.first;
        os << ", ";
        if constexpr (is_inf_type_v<RightT>) os << "+inf";
        else os << bounds_.second;
        os << (r_inc_ ? ']' : ')');
    }

    template <typename OL, typename OR>
    bool sharesPoint(const Interval<OL, OR>& o) const {
        if constexpr (!is_inf_type_v<LeftT> && !is_inf_type_v<OR>) {
            using C = std::common_type_t<LeftT, OR>;
            C a = static_cast<C>(bounds_.first), b = static_cast<C>(o.bounds().second);
            if (a > b || (a == b && !(l_inc_ && o.rightInclusive()))) return false;
        }
        if constexpr (!is_inf_type_v<OL> && !is_inf_type_v<RightT>) {
            using C = std::common_type_t<OL, RightT>;
            C a = static_cast<C>(o.bounds().first), b = static_cast<C>(bounds_.second);
            if (a > b || (a == b && !(o.leftInclusive() && r_inc_))) return false;
        }
        return true;
    }

    template <typename OL, typename OR>
    Interval<double, double> intersect(const Interval<OL, OR>& o) const {
        if (!sharesPoint(o)) {
            throw std::logic_error("Disjoint intervals have no intersection.");
        }
        double l = to_bound_double(bounds_.first, true);
        double ol = to_bound_double(o.bounds().first, true);
        double r = to_bound_double(bounds_.second, false);
        double or_ = to_bound_double(o.bounds().second, false);

        double rl = l > ol ? l : ol;
        bool rli = (l == ol) ? (l_inc_ && o.leftInclusive()) : (l > ol ? l_inc_ : o.leftInclusive());

        double rr = r < or_ ? r : or_;
        bool rri = (r == or_) ? (r_inc_ && o.rightInclusive()) : (r < or_ ? r_inc_ : o.rightInclusive());

        return Interval<double, double>(rl, rr, rli, rri);
    }

    template <typename OL, typename OR>
    Interval<double, double> unite(const Interval<OL, OR>& o) const {
        if (!sharesPoint(o)) {
            throw std::logic_error("Disjoint intervals cannot be united.");
        }
        double l = to_bound_double(bounds_.first, true);
        double ol = to_bound_double(o.bounds().first, true);
        double r = to_bound_double(bounds_.second, false);
        double or_ = to_bound_double(o.bounds().second, false);

        double rl = l < ol ? l : ol;
        bool rli = (l == ol) ? (l_inc_ || o.leftInclusive()) : (l < ol ? l_inc_ : o.leftInclusive());

        double rr = r > or_ ? r : or_;
        bool rri = (r == or_) ? (r_inc_ || o.rightInclusive()) : (r > or_ ? r_inc_ : o.rightInclusive());

        return Interval<double, double>(rl, rr, rli, rri);
    }

private:
    Pair bounds_;
    bool l_inc_;
    bool r_inc_;
};

static bool readBound(const std::string& tok, bool left, bool& inf, double& val) {
    if (tok == "-inf" && left) return inf = true, true;
    if ((tok == "+inf" || tok == "inf") && !left) return inf = true, true;
    try {
        std::size_t pos = 0;
        val = std::stod(tok, &pos);
        inf = false;
        return pos == tok.size();
    } catch (...) {
        return false;
    }
}

int main() {
    Interval<double, double> a(1.0, 10.0, true, false);
    Interval<double, double> b(5.0, 15.0, false, true);
    Interval<std::string, double> c(std::string("-inf"), 8.0, false, true);
    Interval<double, std::string> d(3.0, std::string("+inf"), true, false);

    try {
        std::cout << "Intersect a & b: "; a.intersect(b).print(); std::cout << '\n';
        std::cout << "Union a | b: "; a.unite(b).print(); std::cout << '\n';
        std::cout << "Intersect (-inf, 8] & [3, +inf): "; c.intersect(d).print(); std::cout << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    int n = 0;
    std::cout << "Enter n: ";
    if (!(std::cin >> n) || n <= 0) return 1;

    struct Item { bool li, ri; double l, r; bool linc, rinc; };
    std::vector<Item> arr;
    arr.reserve(static_cast<std::size_t>(n));

    std::cout << "Enter n intervals (e.g. [ 1 10 ) or ( -inf 5 ]):\n";
    for (int i = 0; i < n; ++i) {
        char lb, rb;
        std::string lt, rt;
        Item it{};
        if (!(std::cin >> lb >> lt >> rt >> rb) ||
            (lb != '[' && lb != '(') || (rb != ']' && rb != ')') ||
            !readBound(lt, true, it.li, it.l) || !readBound(rt, false, it.ri, it.r)) {
            std::cerr << "Invalid interval input.\n";
            return 1;
        }
        it.linc = it.li ? false : (lb == '[');
        it.rinc = it.ri ? false : (rb == ']');
        arr.push_back(it);
    }

    bool inf_l = arr[0].li, inf_r = arr[0].ri;
    double cur_l = arr[0].l, cur_r = arr[0].r;
    bool cur_li = arr[0].linc, cur_ri = arr[0].rinc;

    for (int i = 1; i < n; ++i) {
        const auto& x = arr[i];
        if (!inf_l && !x.ri && (cur_l > x.r || (cur_l == x.r && !(cur_li && x.rinc)))) {
            std::cout << "No common intersection.\n";
            return 0;
        }
        if (!x.li && !inf_r && (x.l > cur_r || (x.l == cur_r && !(x.linc && cur_ri)))) {
            std::cout << "No common intersection.\n";
            return 0;
        }
        if (x.li) {
        } else if (inf_l) {
            inf_l = false; cur_l = x.l; cur_li = x.linc;
        } else if (x.l > cur_l) {
            cur_l = x.l; cur_li = x.linc;
        } else if (x.l == cur_l) {
            cur_li = cur_li && x.linc;
        }

        if (x.ri) {
        } else if (inf_r) {
            inf_r = false; cur_r = x.r; cur_ri = x.rinc;
        } else if (x.r < cur_r) {
            cur_r = x.r; cur_ri = x.rinc;
        } else if (x.r == cur_r) {
            cur_ri = cur_ri && x.rinc;
        }

        if (!inf_l && !inf_r && (cur_l > cur_r || (cur_l == cur_r && (!cur_li || !cur_ri)))) {
            std::cout << "No common intersection.\n";
            return 0;
        }
    }

    std::cout << "Common intersection: " << (cur_li ? '[' : '(');
    if (inf_l) std::cout << "-inf"; else std::cout << cur_l;
    std::cout << ", ";
    if (inf_r) std::cout << "+inf"; else std::cout << cur_r;
    std::cout << (cur_ri ? ']' : ')') << '\n';
    return 0;
}