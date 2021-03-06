#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

using namespace std;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {

	VectorXd rmse(4); //Initialize rmse vector of size 1x4
	rmse << 0,0,0,0;  //Define the 4 values to be 0's

	//Check that the size of the data vectors is not zero and that both vectors are the same size
	if (estimations.size()!= ground_truth.size() || estimations.size() == 0){
		std::cout<<"Invalid estimation"<<std::endl;
		return rmse;
	}

	for (int i=0; i<estimations.size(); ++i){
		VectorXd residual = estimations[i] - ground_truth[i];

		residual = residual.array()*residual.array();
		rmse += residual;
	}

	rmse = rmse/estimations.size();
	rmse = rmse.array().sqrt();

	return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
   * TODO:
   * Calculate a Jacobian here.
   */
	//std::cout<<"????????????????????????????????????????????????????????????????????TIME FOR THE JACOBIAN"<<std::endl;
	float px = x_state(0);
	float py = x_state(1);
	float vx = x_state(2);
	float vy = x_state(3);

	
	MatrixXd Hj_(3,4);
	Hj_<< 0.0,0.0,0.0,0.0,
		  0.0,0.0,0.0,0.0,
		  0.0,0.0,0.0,0.0;
	
	float c1 = px*px+py*py;
  	float c2 = sqrt(c1);
  	float c3 = (c1*c2);

  	if (fabs(c2) < 0.0001) {
    std::cout << "CalculateJacobian () - Error - Division by Zero" << endl;
    c2 = 0.0001;
    //return Hj_;
	}

	if (fabs(c1) < 0.0001) {
    std::cout << "CalculateJacobian () - Error - Division by Zero" << endl;
    c1 = 0.0001;
    //return Hj_;
	}

	Hj_ << (px/c2), (py/c2), 0, 0,
      -(py/c1), (px/c1), 0, 0,
      py*(vx*py - vy*px)/c3, px*(px*vy - py*vx)/c3, px/c2, py/c2;

    return Hj_;
}
