clear;clc
close all;
% R = 60;C = 0.000022;L = 1;U = 2;

sys = tf([1],[0.00033, 0.00264, 1]);
t = 0:0.001:3;
y = step(sys, t);
plot(t, y);	hold on;