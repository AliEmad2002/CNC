function [x, y, z] = get_current_pos_from_MCU(MCUserial)
    % Flush port to avoid any paracetic data:
    flush(MCUserial);

    % request from the MCU:
    write(MCUserial,'$',"uint8")

    % read MCU message:
    %[x, y, z] = read(MCUserial,3,"int32");
    a = read(MCUserial,3,"int32");
    x = a(1);
    y = a(2);
    z = a(3);
end