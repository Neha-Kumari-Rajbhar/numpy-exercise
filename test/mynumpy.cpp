#include <pybind11/pybind11.h>
#include <pybind11/stl.h>   // to convert between Python list <-> std::vector
#include <vector>
#include <stdexcept>
#include <iostream>

namespace py = pybind11;

class Array {
public:
    std::vector<double> data;

    Array(const std::vector<double>& v) {
        data = v;
    }

    Array add(const Array& other) const {
        size_t n1 = data.size();
        size_t n2 = other.data.size();

        // Case 1: Same size
        if (n1 == n2) {
            std::vector<double> result(n1);
            for (size_t i = 0; i < n1; ++i) {
                result[i] = data[i] + other.data[i];
            }
            return Array(result);
        }

        // Case 2: Broadcast single value
        if (n2 == 1) {
            std::vector<double> result(n1);
            double val = other.data[0];
            for (size_t i = 0; i < n1; ++i) {
                result[i] = data[i] + val;
            }
            return Array(result);
        }

        if (n1 == 1) {
            std::vector<double> result(n2);
            double val = data[0];
            for (size_t i = 0; i < n2; ++i) {
                result[i] = val + other.data[i];
            }
            return Array(result);
        }

        throw std::invalid_argument("Array sizes are not compatible for addition");
    }

    std::vector<double> to_list() const {
        return data;
    }

    std::string repr() const {
        std::string s = "[";
        for (size_t i = 0; i < data.size(); ++i) {
            s += std::to_string(data[i]);
            if (i != data.size() - 1)
                s += ", ";
        }
        s += "]";
        return s;
    }
};

// Binding code
PYBIND11_MODULE(mynumpy, m) {
    py::class_<Array>(m, "Array")
        .def(py::init<const std::vector<double>&>())
        .def("add", &Array::add)
        .def("to_list", &Array::to_list)
        .def("__repr__", &Array::repr);
}
