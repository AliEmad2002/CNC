function [x, y, z, vx, vy, vz, ax, ay, az] = get_current_pos_from_MCU(MCUserial)
    % Flush port to avoid any paracetic data:
    flush(MCUserial);

    % request from the MCU:
    write(MCUserial,'$',"uint8")

    % read MCU message:
    %[x, y, z, vx, vy, vz, ax, ay, az] = read(MCUserial,3,"int32");
    a = read(MCUserial,9,"int32");
    x = a(1);
    y = a(2);
    z = a(3);
    vx = a(4);
    vy = a(5);
    vz = a(6);
    ax = a(7);
    ay = a(8);
    az = a(9);
end