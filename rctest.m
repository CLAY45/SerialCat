%%rctest.m
clear;clc;
close all;

load file1.txt
a = file1;
b=1:length(a);
plot(b, a);	hold on;

