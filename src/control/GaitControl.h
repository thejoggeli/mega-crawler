#pragma once

#include <Arduino.h>
#include "robot/Robot.h"
#include "gait/IKGait.h"


class GaitControl {
public:

    unsigned long t_start_us = 0;
    unsigned long t_passed_us = 0;
    unsigned long t_last_us = 0;
    unsigned long t_curr_us = 0;
    unsigned long t_delta_us = 0;
    float t_passed;
    float t_delta;

    float gaitTime = 0.0f;
    float gaitSpeed = 0.2f;
    Robot* robot = robot;
    IKGait gait = IKGait(32);

    GaitControl(Robot* robot){
        this->robot = robot;
    }

    void init(){
            
        float gait_timestep = 1.0f / (float)(gait.numFrames);
        for(unsigned int i = 0; i < gait.numFrames; i++){

            float t = (float)(i) * gait_timestep;
            float t2pi = t * PI * 2.0f;
            float tsin = sin(t2pi);

            IKGaitFrame& frame = gait.frames[i];

            float ax = cos(45.0f / 180.0f * PI);
            float ay = sin(45.0f / 180.0f * PI);

            // frame.Q[0].x = +0.15 * ax;
            // frame.Q[1].x = -0.15 * ax;
            // frame.Q[2].x = -0.15 * ax;
            // frame.Q[3].x = +0.15 * ax;
            // frame.Q[0].y = +0.15 * ay;
            // frame.Q[1].y = +0.15 * ay;
            // frame.Q[2].y = -0.15 * ay;
            // frame.Q[3].y = -0.15 * ay;

            // frame.Q[0].z = -0.175f;
            // frame.Q[1].z = -0.175f;
            // frame.Q[2].z = -0.175f;
            // frame.Q[3].z = -0.175f;

            // frame.phi[0] = 0.0f / 180.0f * PI;
            // frame.phi[1] = 0.0f / 180.0f * PI;
            // frame.phi[2] = 0.0f / 180.0f * PI;
            // frame.phi[3] = 0.0f / 180.0f * PI;

            // float dx = tsin * (-0.02);
            // frame.Q[0].x += dx;
            // frame.Q[1].x += dx;
            // frame.Q[2].x += dx;
            // frame.Q[3].x += dx;        

            frame.Q[0].x = +0.265 * ax;
            frame.Q[1].x = -0.265 * ax;
            frame.Q[2].x = -0.265 * ax;
            frame.Q[3].x = +0.265 * ax;

            frame.Q[0].y = +0.265 * ay;
            frame.Q[1].y = +0.265 * ay;
            frame.Q[2].y = -0.265 * ay;
            frame.Q[3].y = -0.265 * ay;

            frame.Q[0].z = -0.033;
            frame.Q[1].z = -0.033;
            frame.Q[2].z = -0.033;
            frame.Q[3].z = -0.033;

            frame.phi[0] = 45.0f / 180.0f * PI;
            frame.phi[1] = 45.0f / 180.0f * PI;
            frame.phi[2] = 45.0f / 180.0f * PI;
            frame.phi[3] = 45.0f / 180.0f * PI;

            float dz = (tsin*0.5+0.5f) * (-0.05);
            frame.Q[0].z += dz;
            frame.Q[1].z += dz;
            frame.Q[2].z += dz;
            frame.Q[3].z += dz;
            
            float dphi = (tsin*0.5+0.5f) * (15.0f) * (1.0f/180.0f) * PI;
            frame.phi[0] += dphi;
            frame.phi[1] += dphi;
            frame.phi[2] += dphi;
            frame.phi[3] += dphi; 

        }
    }

    void start(){

        t_last_us = t_start_us = micros();

    }

    void update(){
        
        t_curr_us = micros();
        t_delta_us = t_curr_us - t_last_us;
        t_delta = t_delta_us*1.0e-6;
        t_passed_us = t_curr_us - t_start_us;
        t_passed = t_passed_us*1.0e-6;
        
        Serial.println(String("IKGaitFrame at gaitTime=") + String(gaitTime, 3));

        // Benchmark::tick();
        IKGaitFrame frame;
        gait.getFrameRelativeInterp(gaitTime, frame);
        // Benchmark::tock("getFrameRelativeInterp duration: ");
        // frame.print();

        // Benchmark::tick();
        float angles_out[NUM_LEGS][NUM_JOINTS];
        Leg::IKState ikStates[NUM_LEGS];
        bool ikFailed = false;
        for(int i = 0; i < NUM_LEGS; i++){
            ikStates[i] = robot->legs[i].ik(frame.Q[i], frame.phi[i], angles_out[i]);
            if(ikStates[i] != Leg::IKState::OK){
                ikFailed = true;
            }
            // if(ikStates[i] != Leg::IKState::OK){
            //     for(int j = 0; j < NUM_JOINTS; j++){
            //         angles_out[i][j] = 0.0f;
            //     }
            // }
        }
        // Benchmark::tock("legs.ik() duration: ");
        
        // for(int i = 0; i < NUM_LEGS; i++){
        //     Leg::printAngles(angles_out[i]);
        // }

        // for(int i = 0; i < NUM_LEGS; i++){
        //     Leg::IKState ikState = ikStates[i];
        //     if(ikState == Leg::IKState::AngleLimitsError){
        //         Serial.println("Leg::IKState::AngleLimitsError");
        //     } else if(ikState == Leg::IKState::NoSolutionError){
        //         Serial.println("Leg::IKState::NoSolutionError");
        //     } else if(ikState == Leg::IKState::OK){
        //         Serial.println("Leg::IKState::OK");
        //     } else {
        //         Serial.println("unhandled Leg::IKState");
        //     }
        // }

        if(!ikFailed){
            float moveSeconds = t_delta * gaitSpeed;
            for(int i = 0; i < NUM_LEGS; i++){
                for(int j = 0; j < NUM_JOINTS; j++){
                    robot->legs[i].joints[j].setAngle(angles_out[i][j], moveSeconds);
                }
            }
        } else {
            Serial.println("IK failed");
        }

        gaitTime += t_delta * gaitSpeed;
        while(gaitTime > 1.0f){
            gaitTime -= 1.0f;
        }

        t_last_us = t_curr_us;
        
    }

};