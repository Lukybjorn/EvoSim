//
// Created by nevo9 on 19/10/2024.
//

#include "Network.h"

Network::Network(const int input_nodes, const int processing_layers, const std::vector<int> &processing_nodes, const int output_nodes, bool randit)
                : _input_nodes(input_nodes), _processing_layers(processing_layers),
                  _processing_nodes(processing_nodes), _output_nodes(output_nodes) {
    if (processing_layers != processing_nodes.size()) {
        std::cerr << "Number of proccesing_layers and processing_nodes don't match!" << std::endl;
        exit(1);
    }
    // Initialize the member variables directly
    Eigen::VectorXf vec_in(this->_input_nodes);
    Eigen::VectorXf vec_out(this->_output_nodes);
    vec_in.setOnes();
    vec_out.setZero();
    this->_input_vector = vec_in;
    if (randit) {
        this->_processing_vectors = make_processing_vectors(PROCESSING_TYPE::RAND);
        this->_connection_matrices = make_connection_matrices(PROCESSING_TYPE::RAND);
    } else {
        this->_processing_vectors = make_processing_vectors();
        this->_connection_matrices = make_connection_matrices();
    }

    this->_output_vector = vec_out;
}

Eigen::VectorXf Network::make_processing_vector(const int nodes, const PROCESSING_TYPE type) {
    Eigen::VectorXf processing_vector(nodes);
    switch (type) {
        case PROCESSING_TYPE::ZEROS:
            processing_vector.setZero();
        break;
        case PROCESSING_TYPE::ONES:
            processing_vector.setOnes();
        break;
        case PROCESSING_TYPE::RAND:
            processing_vector.setRandom();
        break;
        default:
            std::cerr << "Need to add type of processing vector!" << std::endl;
            exit(1);
    }
    return processing_vector;
}

Eigen::MatrixXf Network::make_connection_matrix(const int rows, const int cols, const PROCESSING_TYPE type) {
    Eigen::MatrixXf connection_matrix(rows, cols);
    switch (type) {
        case PROCESSING_TYPE::ZEROS:
            connection_matrix.setZero();
        break;
        case PROCESSING_TYPE::ONES:
            connection_matrix.setOnes();
        break;
        case PROCESSING_TYPE::IDENTITY:
            connection_matrix.setIdentity();
        break;
        case PROCESSING_TYPE::RAND:
            connection_matrix.setRandom();
        break;
        default:
            std::cerr << "Need to add type of connection matrix!" << std::endl;
        exit(1);
    }
    return connection_matrix;
}

std::vector<Eigen::VectorXf> Network::make_processing_vectors(const PROCESSING_TYPE type) const {
    std::vector<Eigen::VectorXf> processing_vectors;
    for (int i = 0; i < this->_processing_layers; i++) {
        Eigen::VectorXf vec = make_processing_vector(this->_processing_nodes[i], type);
        processing_vectors.push_back(vec);
    }
    return processing_vectors;
}

std::vector<Eigen::MatrixXf> Network::make_connection_matrices(const PROCESSING_TYPE type) const {
    std::vector<Eigen::MatrixXf> connection_matrices;
    Eigen::MatrixXf f_mat = make_connection_matrix(this->_processing_nodes[0], this->_input_nodes, type);
    connection_matrices.push_back(f_mat);
    for (int i = 0; i < this->_processing_layers - 1; i++) {
        Eigen::MatrixXf mat = make_connection_matrix(this->_processing_nodes[i + 1], this->_processing_nodes[i], type);
        connection_matrices.push_back(mat);
    }
    f_mat = make_connection_matrix(this->_output_nodes, this->_processing_nodes.back(), type);
    connection_matrices.push_back(f_mat);
    return connection_matrices;
}

void Network::calculate_output_vector() {
    Eigen::VectorXf result = this->_connection_matrices[0] * this->_input_vector;
    for (int i = 0; i < this->_processing_layers; i++) {
        result = result + this->_processing_vectors[i];
        result = this->_connection_matrices[i + 1] * result;
    }
    this->_output_vector = result;
}