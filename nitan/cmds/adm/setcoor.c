// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// setcoor.c

inherit F_CLEAN_UP;

#define SYNTAX          "syntax: setcoor x,y,z\n"
#define VALUE           query("env/setcoor", this_player(1))
//#define VALUE           10

mapping map_dirs = ([
        "enter"     :    ([ "x" : -1,    "y" : -1,    "z": -1    ]),
        "out"       :    ([ "x" :  1,    "y" :  1,    "z":  1    ]),
        "east"      :    ([ "x" : VALUE, "y" :  0,    "z":  0    ]),
        "west"      :    ([ "x" :-VALUE, "y" :  0,    "z":  0    ]),
        "south"     :    ([ "x" :  0,    "y" :-VALUE, "z":  0    ]),
        "north"     :    ([ "x" :  0,    "y" : VALUE, "z":  0    ]),
        "up"        :    ([ "x" :  0,    "y" :  0,    "z": VALUE ]),
        "down"      :    ([ "x" :  0,    "y" :  0,    "z":-VALUE ]),
        "eastup"    :    ([ "x" : VALUE, "y" :  0,    "z": VALUE ]),
        "westup"    :    ([ "x" :-VALUE, "y" :  0,    "z": VALUE ]),
        "southup"   :    ([ "x" :  0,    "y" :-VALUE, "z": VALUE ]),
        "northup"   :    ([ "x" :  0,    "y" : VALUE, "z": VALUE ]),
        "eastdown"  :    ([ "x" : VALUE, "y" :  0,    "z":-VALUE ]),
        "westdown"  :    ([ "x" :-VALUE, "y" :  0,    "z":-VALUE ]),
        "southdown" :    ([ "x" :  0,    "y" :-VALUE, "z":-VALUE ]),
        "northdown" :    ([ "x" :  0,    "y" : VALUE, "z":-VALUE ]),
        "southeast" :    ([ "x" : VALUE, "y" :-VALUE, "z":  0    ]),
        "northeast" :    ([ "x" : VALUE, "y" : VALUE, "z":  0    ]),
        "southwest" :    ([ "x" :-VALUE, "y" :-VALUE, "z":  0    ]),
        "northwest" :    ([ "x" :-VALUE, "y" : VALUE, "z":  0    ]),
]);

int non_recur_do(object room, int x, int y, int z, string prefix);
void clear_old_coor(object room);
int help(object me);

int main(object me, string arg)
{
        int    x, y, z;
        int    the_same_dir = 0, all = 0;
        object env = environment(me);
        string prefix, file;

        seteuid(getuid());

        if( !SECURITY_D->valid_grant(me, "(admin)") )
                return 0;

        if( !query("env/setcoor", me) )
                return notify_fail("危險指令，慎用！慎用！\n");

        set_eval_limit(900000000);
        reset_eval_cost();

        if( !arg ) {
                if( query("border", env)){
                        write("房間 " + base_name(env) + " 已非邊界。\n");
                        delete("border", env);
                        return 1;
                } else
                        return notify_fail("這裏本來就不是邊界。\n");
        }

        if( member_array(arg, keys(map_dirs)) != -1 ) {
                if( query("border/"+arg, env) ) {
                        write("房間 " + base_name(env) + " 的" + arg + "方向已非邊界。\n");
                        delete("border/"+arg, env);
                        if( !sizeof(query("border", env)) )
                                delete("border", env);
                        return 1;
                } else {
                        set("border/"+arg, 1, env);
                        write("房間 " + base_name(env) + " 的" + arg + "方向已設為邊界。\n");
                        return 1;
                }
        }

        if( sscanf(arg, "-s %s", arg) )
                the_same_dir = 1;

        else
        if( sscanf(arg, "-a %s", arg) )
                all = 1;

        if( sscanf(arg, "%d,%d,%d", x, y, z) != 3 )
                return notify_fail(SYNTAX);

        prefix = "";

        if( !all )
                prefix = base_dir(env);

        if( the_same_dir || all ) {
                non_recur_do(env, x, y, z, prefix);
        } else {
                if( query("coor", env) )
                        clear_old_coor(env);

                if( query("coor", env) != 0 )
                        write("房間 " + base_name(env) + " 座標重新設定成功。\n");
                else
                        write("房間 " + base_name(env) + " 座標設定成功。\n");
                set("coor/x", x, env);
                set("coor/y", y, env);
                set("coor/z", z, env);
                file = read_file(base_name(env) + ".c");
                file = replace_string(file, "setup()",
                       sprintf("set(\"coor/x\", %d);\n\tset(\"coor/y\", %d);\n\tset(\"coor/z\", %d);\n\tsetup()",
                                x, y, z));
                write_file(base_name(env) + ".c", file, 1);
        }

        write("ok\n");
        return 1;
}

int non_recur_do(object room, int x, int y, int z, string prefix)
{
        mapping roomlist, all;
        mapping border;
        mapping exits;
        string *directions;
        string *dirs;
        string dir, file;
        object curr_room, next_room;
        int i;
        int file_count = 0;
        int x1, y1, z1;

        if( query("coor", room) )
                clear_old_coor(room);

        all = ([]);
        roomlist = ([]);

        set("coor/x", x, room);
        set("coor/y", y, room);
        set("coor/z", z, room);
        file = read_file(base_name(room) + ".c");
        file = replace_string(file, "setup()",
                sprintf("set(\"coor/x\", %d);\n\tset(\"coor/y\", %d);\n\tset(\"coor/z\", %d);\n\tsetup()",
                        x, y, z));
        write_file(base_name(room) + ".c", file, 1);
        file_count ++;
        write("房間 " + base_name(room) + " 座標設定成功。\n");
        all += ([base_name(room) : room]);
        roomlist += ([base_name(room) : room]);

        x1 = y1 = z1 = 0;
        while( sizeof(roomlist) )
        {

                reset_eval_cost();

                dirs = ({});

                curr_room = values(roomlist)[0];
                map_delete(roomlist, keys(roomlist)[0]);

                if( mapp(border=query("border", curr_room)) )
                        dirs = keys(border);

                exits=query("exits", curr_room);
                if( !mapp(exits) || !sizeof(exits))
                        return 1;

                directions = keys(exits);
                directions -= dirs;

                x=query("coor/x", curr_room);
                y=query("coor/y", curr_room);
                z=query("coor/z", curr_room);

                for( i = 0; i < sizeof(directions); i ++ )
                {
                        reset_eval_cost();

                        dir = directions[i];

                        if( !objectp(next_room = get_object(exits[dir])) )
                                continue;

                        if( undefinedp(all[base_name(next_room)]) &&
                            (strsrch(base_name(next_room), prefix) != -1 || prefix == "") ) {
                                if( query("coor", next_room) )
                                        clear_old_coor(next_room);

                                if( map_dirs[dir] )
                                {
                                        x1 = x + map_dirs[dir]["x"];
                                        y1 = y + map_dirs[dir]["y"];
                                        z1 = z + map_dirs[dir]["z"];
                                } else
                                {
                                        x1 = x + 1;
                                        y1 = y + 1;
                                        x1 = z + 1;
                                }

                                set("coor/x", x1, next_room);
                                set("coor/y", y1, next_room);
                                set("coor/z", z1, next_room);

                                file = read_file(base_name(next_room) + ".c");
                                file = replace_string(file, "setup()",
                                        sprintf("set(\"coor/x\", %d);\n\tset(\"coor/y\", %d);\n\tset(\"coor/z\", %d);\n\tsetup()",
                                                x1, y1, z1));
                                write_file(base_name(next_room) + ".c", file, 1);
                                file_count ++;
                                write("房間 " + base_name(next_room) + " 座標設定成功。\n");

                                all += ([base_name(next_room) : next_room]);
                                roomlist += ([base_name(next_room) : next_room]);
                        }
                }
        }
        write("共定位 " + sprintf("%d", file_count) + " 個房間。\n");
        return 1;
}

void clear_old_coor(object room)
{
        int x, y, z, i;
        string *file;
        string result = "";

        x=query("coor/x", room);
        y=query("coor/y", room);
        z=query("coor/z", room);

        file = explode(read_file(base_name(room) + ".c"), "\n");
        for (i = 0; i < sizeof(file); i++) {
                if( strsrch(file[i], "set(\"coor/") != -1) {
                        file[i] = 0; continue;
                }
                // file[i] = replace_string(file[i],
                //      sprintf("set(\"coor/y\", %d);\n", y), "");
        }
        file -= ({ 0 });
        result += implode(file, "\n");
        rm(base_name(room) + ".c");
        write_file(base_name(room) + ".c", result, 1);
}

int help(object me)
{
write(@HELP
指令格式 :
        setcoor <參數> x,y,z

用法：
        setcoor            清除當前房間所有方向的邊界屬性。
        setcoor <方向>     若該當前房間的該方向已為邊界，則清除之，否則
                           設置該方向為邊界。
        setcoor x,y,z      無論當前房間是否已定位，重新並單獨處理該房間。
        setcoor -s x,y,z   無論當前房間是否已定位，重新定位當前房間的坐
                           標，並連鎖處理，直到同一目錄下所有房間都被處
                           理過為止。
        setcoor -a x,y,z   同上，但無同一目錄限制。

HELP
);
    return 1;
}
