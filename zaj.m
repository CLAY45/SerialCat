clc;clear;close all;

x = xlsread('file.xlsx','sheet1','a1:a40');
y = xlsread('file.xlsx','sheet1','b1:b40');
figure(1)
plot(x,y);hold on;
plot(x,y,'.');hold off

x = xlsread('file.xlsx','sheet2','a1:a40');
y = xlsread('file.xlsx','sheet2','b1:b40');
figure(2)
plot(x,y);hold on;
plot(x,y,'.');hold off;