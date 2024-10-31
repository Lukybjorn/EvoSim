//
// Created by nevo9 on 19/10/2024.
//

#pragma once

#include <iostream>
#include <ostream>
#include <Eigen/Dense>


enum class PROCESSING_TYPE {
    ZEROS,
    ONES,
    IDENTITY,
    RAND,
    CUSTOM
};


class Network {
private:
    const int _input_nodes;
    const int _processing_layers;
    std::vector<int> _processing_nodes;
    const int _output_nodes;
    Eigen::VectorXf _input_vector;
    std::vector<Eigen::VectorXf> _processing_vectors;
    std::vector<Eigen::MatrixXf> _connection_matrices;
    Eigen::VectorXf _output_vector;
public:
    /**
     * @brief constructor for the Network class
     * @param input_nodes number of nodes in the input layer
     * @param processing_layers number of layers with input nodes
     * @param processing_nodes list (std::vector) with the number of nodes in each layer
     * @param output_nodes number of nodes in the output layer
     * @param randit if true, set the processing_vectors and connection_matrices to random values, default false
     */
    Network(int input_nodes, int processing_layers, const std::vector<int> &processing_nodes, int output_nodes, bool randit = false);

    // Getters and Setters

    [[nodiscard]] int input_nodes() const {
        return _input_nodes;
    }

    [[nodiscard]] int processing_layers() const {
        return _processing_layers;
    }

    [[nodiscard]] std::vector<int> processing_nodes() const {
        return _processing_nodes;
    }

    [[nodiscard]] int output_nodes() const {
        return _output_nodes;
    }

    [[nodiscard]] Eigen::VectorXf input_vector() const {
        return _input_vector;
    }

    [[nodiscard]] std::vector<Eigen::VectorXf> processing_vectors() const {
        return _processing_vectors;
    }

    [[nodiscard]] std::vector<Eigen::MatrixXf> connection_matrices() const {
        return _connection_matrices;
    }

    [[nodiscard]] Eigen::VectorXf output_vector() const {
        return _output_vector;
    }

    void set_processing_nodes(const std::vector<int> &processing_nodes) {
        this->_processing_nodes = processing_nodes;
    }

    void set_input_vector(const Eigen::VectorXf &input_vector) {
        this->_input_vector = input_vector;
    }

    void set_processing_vectors(const std::vector<Eigen::VectorXf> &processing_vectors) {
        this->_processing_vectors = processing_vectors;
    }

    void set_connection_matrices(const std::vector<Eigen::MatrixXf> &connection_matrices) {
        this->_connection_matrices = connection_matrices;
    }

    void set_output_vector(const Eigen::VectorXf &output_vector) {
        this->_output_vector = output_vector;
    }

    friend std::ostream & operator<<(std::ostream &os, const Network &obj) {
        os << "input_nodes: " << obj._input_nodes
           << "\ninput_vector: \n" << obj._input_vector
           << "\nprocessing_layers: " << obj._processing_layers;
        for (int i = 0; i < obj._processing_layers; i++) {
            os << "\nconnection_matrix: \n" << obj._connection_matrices[i];
            os << "\nprocessing_vector: \n" << obj._processing_vectors[i];
        }
        os << "\nconnection_matrix: \n" << obj._connection_matrices.back();

        os << "\noutput_nodes: " << obj._output_nodes
           << "\noutput_vector: \n" << obj._output_vector;

        return os;
    }

    // class methods
    /**
     * @brief Creates a processing vector with a specified number of nodes and processing type.
     *
     * @param nodes The number of nodes in the processing vector.
     * @param type The type of processing vector to create.
     * @return A processing vector of type Eigen::VectorXf.
     */
    static Eigen::VectorXf make_processing_vector(int nodes, PROCESSING_TYPE type = PROCESSING_TYPE::ZEROS);

    /**
     * @brief Creates a connection matrix based on the size of the previous and following layers and processing type.
     *
     * @param rows The number of nodes in the following layer.
     * @param cols The number of nodes in the previous layer.
     * @param type The type of processing vector to create.
     * @return A processing vector of type Eigen::VectorXf.
     */
    static Eigen::MatrixXf make_connection_matrix(int rows, int cols, PROCESSING_TYPE type = PROCESSING_TYPE::IDENTITY);

    /**
     * @brief Creates a list (std::vector) of processing_vectors based on the type specified
     * @param type set the type of all of the processing_vectors, default - zero
     * @return returns a std::vector<Eigen::VectorXf> that contains all of the processing_vectors
     */
    [[nodiscard]] std::vector<Eigen::VectorXf> make_processing_vectors(PROCESSING_TYPE type = PROCESSING_TYPE::ZEROS) const;

    /**
     * @brief Creates a list (std::vector) of connecting_matricies based on the type specified
     * @param type set the type of all of the connecting_matricies, default - identity
     * @return returns a std::vector<Eigen::MatrixXf> that contains all of the connecting_matricies
     */
    [[nodiscard]] std::vector<Eigen::MatrixXf> make_connection_matrices(PROCESSING_TYPE type = PROCESSING_TYPE::IDENTITY) const;

    /**
     * @brief calculate the output_vector and set the m_output_vector to the value
     */
    void calculate_output_vector();
};

