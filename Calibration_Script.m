% Samuel Lee Toepke
% samueltoepke@gmail.com
% Spring 2015
% Voltage_ADC_Calibrate.m: For the chipKIT Max32 voltage sensing calibration example. 
%   Used a DMM to measure common voltages from a DC power supply. 
%   This Octave (or MATLAB) file finds a slope and offset modifier that can improve the reading by an ~order of magnitude.
%   The desired outputs of this operation are 'slope_modifier' and 'offset_modifier'...add them to the Max32 voltage sensing code.
%   Using a variable DC power supply with more data points will give a better calibration. Alas, all I had available at the time 
%   was a throwaway ATX power supply.

% X-Axis
  x = [1:1:3];

% Voltages from digital multimeter. Get average line, slope and offset.
  dmm = [3.34 5.05 11.76];
  p = polyfit(x,dmm,1);
  slope_dmm_average = p(1);
  offset_dmm_average = p(2);

% Voltages from chipkit after voltage divider and ADC code. Get average line, slope and offset.
  chipkit = [3.38 5.13 11.98];
  p = polyfit(x,chipkit,1);
  slope_chipkit_average = p(1);
  offset_chipkit_average = p(2);

% Calculate modification values.
slope_modifier = slope_dmm_average/slope_chipkit_average
offset_modifier = offset_dmm_average - offset_chipkit_average

chipkit_modified = (chipkit * slope_modifier) + offset_modifier;
average_error_without_calibration = mean(abs(dmm - chipkit))
average_error_with_calibration = mean(abs(dmm - chipkit_modified))