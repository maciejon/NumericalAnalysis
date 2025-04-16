#include <functional>
#include <vector>
#include <string>

double transform(double x, double a, double b);

struct GaussLegendre {
    std::vector<double> nodes;
    std::vector<double> weights;

    GaussLegendre(int n) {
        switch (n) {
            case 2:
                nodes = {-1.0 / sqrt(3), 1.0 / sqrt(3)};
                weights = {1.0, 1.0};
                break;
            case 3:
                nodes = {-sqrt(3.0/5), 0.0, sqrt(3.0/5)};
                weights = {5.0/9, 8.0/9, 5.0/9};
                break;
            case 4:
                nodes = {-0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116};
                weights = {0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451};
                break;
            default:
                throw std::invalid_argument("Obsługiwane tylko 2, 3 lub 4 węzły");
        }
    }

    double integrate(std::function<double(double)> f, double a, double b) {
        double sum = 0.0;
        for (size_t i = 0; i < nodes.size(); ++i) {
            double xi = transform(nodes[i], a, b);
            sum += weights[i] * f(xi);
        }
        return sum * (b - a) / 2.0;
    }
};
double f1(double x);
double f2(double x);

void test_function(std::function<double(double)> f, double exact, double a, double b, const std::string& name);
double section_integrate(std::function<double(double)> f, double a, double b, int n_intervals, int n_nodes);
