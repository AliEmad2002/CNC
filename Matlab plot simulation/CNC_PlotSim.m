clear all
close all
clc

%% configuration:
x_min = -10*800;
x_max = 300*800;
y_min = -10*800;
y_max = 300*800;
z_min = 0*800;
z_max = 100*800;
z_material = 0;
z_updaterate = 1000; % number of iterations to update z-axis color

port = "COM15";
baudrate = 115200;

%% prepare plot parameters:
h_material = animatedline;
h_air = animatedline("Color", [1 1 1], "Marker", "*");
axis([x_min, x_max, y_min, y_max]);

%% Init UART connection:
MCUserial = serialport(port, baudrate, "Timeout",20);

%% read from MCU and draw:
i = 0;
isFirstAfterAir = 0;
while 1
    [x, y, z, vx, vy, vz, ax, ay, az] = get_current_pos_from_MCU(MCUserial);

    % if z-axis is low enough to carve the material, update material curve:
    if (z < z_material)
        % if this is first point of current material curve, create new one:
        if (isFirstAfterAir == 1)
            h_material = animatedline;
            isFirstAfterAir = 0;
        end 
        addpoints(h_material, x, y);       
    else
        % otherwise, z-axis is in the air, update the air point:
        isFirstAfterAir = 1;
        if (i == z_updaterate)
            i = 0;
            %delete(h_air);
            %c = (z-z_min)/(z_max-z_min);
            %h_air = animatedline("Color", [c 1 1], "Marker", '*');
        end
    end
    %addpoints(h_air, x, y);
    drawnow limitrate;
    i = i + 1;
end