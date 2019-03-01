// taskd.c
// 茼蜆樓奻呴撈汜傖bossㄛ伀侚綴鳳昜

#define TASK_DIR        "/task/"
#define TASK_OB_DIR     TASK_DIR + "obj/"
#define QUEST_LIST      TASK_DIR + "questlist/"
#define ZONES           TASK_DIR + "zones"
#define RESET_T         1800
#define DELAY_RESET_T   180
#define CONSULT         10
#define MIN(x, y)       (x > y ? y : x)
#define BIG_TASK_N      6
#define BIG_TRADER      find_living("tang nan")
#define SHADOW_ENV      "/task/shadow_room"
#define SEARCH_TIMES    10
#define ROOM_TYPE       1
#define DEBUGER         "lonely"
#define TP(x)           tell_object(find_player(DEBUGER), x)
#define DEBUG

#include <ansi.h>
#include <command.h>
inherit F_DBASE;

#include "/task/questlist/item"

void    init_task();
void    alloc_task(string arg, int i);
void    delay_init_task();
string  display_locate(int dist, string alti, string dire, string city);
string  ask_for_task(object me, string arg);
void    finish(object ob, object me);
void    reg_info(string arg, object env, int i);
int     die(object me);

nosave mapping *task_status;
nosave mapping search_room;

mapping query_sroom() {return search_room;}
mapping *query_task() {return task_status;}

nosave string  *symbol = ({"＿", "﹤", "∥", "ˍ", "﹣", "∣", "ˉ", "<=", "↘", "ˇ", "=>", "↙", "沅", "沛", "汪", "沉", "//", "ㄞ", "\\\\", "", "||", "′","==", "／", "↗", "←", "↑", "⊙", "↓", "⊕", "♂", "♀"});
nosave string  *colors = ({RED, GRN, YEL, BLU, MAG, CYN, WHT, HIR, HIG, HIY, HIB, HIM, HIC, HIW});

void remove()
{
        string  task_ob;
        mapping stat;

        remove_call_out("delay_init_task");
        remove_call_out("init_task");

        if (sizeof(task_status))
        {
                foreach (stat in task_status)
                {
                        if (! mapp(stat) ||
                            undefinedp(stat["env"]))
                                continue;

                        if (objectp(stat["env"]) &&
                            stat["env"]->is_character() &&
                            ! userp(stat["env"]))
                        {
                                delete("inquiry/"+filter_color(stat["name"]), stat["env"]);
                                delete_temp("task", stat["env"]);
                                delete_temp("override/accept_object", stat["env"]);
                                stat["env"]->delete_override("die");
                        } else
                        if (objectp(stat["env"]) && stat["env"]->is_room())
                                delete_temp("search_objects", stat["env"]);
                }
        }
        task_status = allocate(0);
}

void remove_task()
{
        remove_call_out("delay_init_task");
        remove_call_out("init_task");
        task_status = allocate(0);
}

int clean_up() { return 1; }

void create()
{
        seteuid(getuid());
        set("channel_id", "妏韜儕鍾");
        get_object("/d/city/dangpu");
        init_task();
}

void init_task()
{
        int i = 0;
        string *task_objs = get_dir(TASK_OB_DIR);
        string  task_ob, temp_big_task;
        mapping stat;
        object ob;

        foreach (string file in task_objs)
                if (objectp(ob = find_object(TASK_OB_DIR + file)))
                        destruct(ob);

        if (sizeof(task_status))
        {
                foreach (stat in task_status)
                {
                        if (! mapp(stat) ||
                            undefinedp(stat["env"]))
                                continue;

                        if (objectp(stat["env"]) &&
                            stat["env"]->is_character() &&
                            ! userp(stat["env"]))
                        {
                                delete("inquiry/"+filter_color(stat["name"]), stat["env"]);
                                delete_temp("task", stat["env"]);
                                delete_temp("override/accept_object", stat["env"]);
                                stat["env"]->delete_override("die");
                        } else
                        if (objectp(stat["env"]) && stat["env"]->is_room())
                                delete_temp("search_objects", stat["env"]);
                }
        }

        task_status = allocate(sizeof(task_objs));

        search_room = ([]);

        if (! find_object("/d/city/dangpu"))
                load_object("/d/city/dangpu");

        BIG_TRADER->clean_big_task(BIG_TASK_N);

        for (int j = 0; j < BIG_TASK_N; j++) {
                temp_big_task = task_objs[random(sizeof(task_objs))];
                task_objs -= ({temp_big_task});
                BIG_TRADER->add_big(temp_big_task, j);
                reg_info(temp_big_task, get_object(SHADOW_ENV), (sizeof(task_status) - j - 1));
        }

        foreach(task_ob in task_objs)
                alloc_task(task_ob, i++);

        BIG_TRADER->task_announce();

        /************************************************
         message("system", "==========================================\n"
                           "            妏韜昢煦饜俇救              \n"
                           "==========================================\n",
                           filter_array(users(),(:!query("env/no_task", $1):)));
        ************************************************/

        remove_call_out("delay_init_task");
        call_out("delay_init_task", RESET_T - DELAY_RESET_T);
}

void delay_init_task()
{
        message("system", HIW "▽妏韜儕鍾▼妏韜昢蔚衾煦笘綴笭陔煦饜﹝\n" NOR,
                //filter_array(users(),(:!query("env/no_task", $1):)));
                users());
        remove_call_out("init_task");
        call_out("init_task", DELAY_RESET_T);
}

void alloc_task(string arg, int i)
{
        string *zones, *rooms;
        string zone, room;
        object room_ob, inv, *invs, *target = ({});
        object task_ob, target_ob, env;

        zones = explode(read_file(ZONES), "\n");
        zone = zones[random(sizeof(zones))];
        rooms = get_dir(zone);
        room = zone + rooms[random(sizeof(rooms))];

        while (sizeof(rooms) > 0)
        {
                if( file_size(room) == -2 || room[<2..<1] != ".c" || !query("coor", get_object(room)) ) {
                        rooms -= ({ room });
                        room = zone + rooms[random(sizeof(rooms))];
                } else break;
        }

        if (sizeof(rooms) < 1 || ! objectp(room_ob = get_object(room)))
        {
                alloc_task(arg, i);
                return;
        }

        invs = all_inventory(room_ob);

        foreach (inv in invs)
                if (((inv->is_character() && ! userp(inv) &&
                    query("race", inv) != "珧忤" && 
                    !query_temp("quest_ob", inv) && 
                    ! inv->is_stay_in_room() &&
                    ! inv->is_vendor() &&
                    ! inv->is_master()) || inv->is_container()) &&
                    !sizeof(filter_array(all_inventory(inv),(:query("task_ob", $1):))) )
                        target += ({ inv }); // target is npc or container

        if (! sizeof(target))
        {
                if (sizeof(search_room) && member_array(base_name(room_ob), keys(search_room)) != -1)
                {
                        alloc_task(arg, i);
                        return;
                }

                target = ({ room_ob });
                search_room += ([base_name(room_ob) : arg]);
        }

        if (objectp(task_ob = find_object(TASK_OB_DIR + arg)))
                destruct(task_ob);
        task_ob = load_object(TASK_OB_DIR + arg);

        set("task_ob", 1, task_ob);
        delete("big_task", task_ob);
        delete("keeper_killer", task_ob);
        delete("geter", task_ob);
        set("can_beg", 90, task_ob);
        target_ob = target[random(sizeof(target))];
        if (target_ob->is_room())
        {
                mapping data;

                data = ([ base_name(task_ob) : 2000000 ]);
                set_temp("search_objects", data, target_ob);
        } else
        {
                delete_temp("override/accept_object", task_ob);
                task_ob->delete_override("die");
                task_ob->move(target_ob, 1);
        }

        if (! objectp(env = environment(task_ob)))
                env = target_ob;

        reg_info(arg, env, i);
}

void reg_info(string arg, object env, int i)
{
        object task_ob;

        task_ob = get_object(TASK_OB_DIR + arg);

        if (! objectp(env))
                env = get_object(SHADOW_ENV);

        task_status[i]=(["name":query("name", task_ob),
                            "id":query("id", task_ob),
                            "owner":query("owner", task_ob),
                            "file"  :   arg,
                            "flag"  :   0,
                            "env"   :   env,
        ]);

        if (objectp(task_status[i]["env"]) &&
            objectp(environment(task_status[i]["env"])) &&
            task_status[i]["env"]->is_character() &&
            ! task_status[i]["env"]->is_master())
            // ! function_exists("accept_object", task_status[i]["env"]))
        {
                if( query_temp("override/accept_object", task_status[i]["env"]) )
                        return;

                if( query("race", task_status[i]["env"]) == "珧忤" )
                        return;

                set("inquiry/"+filter_color(task_status[i]["name"]),
                        (: call_other, __FILE__, "ask_for_task", task_status[i]["env"],
                        filter_color(task_status[i]["name"]) :), task_status[i]["env"]);
                set_temp("override/accept_object",
                        (: call_other, __FILE__, "accept_object" :), task_status[i]["env"]);

                task_status[i]["env"]->set_override("die",
                        (: call_other, __FILE__, "die" :));
        }

}


string task_list()
{
        int i = 1;
        string tmp = "", res = "";
        mapping task_info;

        if (! sizeof(task_status))
                return "醴遜羶衄睡妏韜掩炵苀煦饜﹝\n";

        foreach (task_info in task_status) {
                tmp = sprintf("%2s%s腔◇%s◆(%s)", task_info["flag"] ?
                        WHT "﹟" NOR : "", task_info["owner"],
                        task_info["name"], task_info["id"]);
                res += sprintf("%s%" + (38 - strlen(filter_color(tmp))) + "s", tmp, "");
                res += i % 2 ? "" : "\n";
                i++;
        }

        return res[<1..<1] == "\n" ? res : res + "\n";
}

string locate_ob(object me, string arg)
{
        string *altitude =({
                "詢揭", "華源", "腴揭"
        });
        string *directions=({
                "笚峓","控源", "鰍源", "陲源","昹源",
                "陲控源","昹控源","陲鰍源","昹鰍源"
        });

        int dis, x_sub, y_sub, z_sub, task_size = sizeof(task_status) - BIG_TASK_N;
        string alt, dir, city;
        object env, room, ob;
        mapping obj_info, coor_there, coor_here = query("coor", environment(me));

        for (int i = 0; i < task_size; i++) {
                obj_info = task_status[i];
                if (obj_info["id"] == arg || filter_color(obj_info["name"]) ==  arg) {
                        call_other(TASK_OB_DIR + obj_info["file"], "???");
                        ob = find_object(TASK_OB_DIR + obj_info["file"]);
                        if (obj_info["flag"])
                                return "◇" + obj_info["name"] + "◆眒冪昜寥埻翋賸ㄛ斕遜梑妦繫ˋ\n";

                        /*
                        if( objectp(ob) && query("geter", ob) && playerp(environment(ob)) )
                                return "◇" + obj_info["name"] + "◆眒冪衄鏽善賸ㄛ斕遜梑妦繫ˋ\n";
                        */
                        if (! objectp(env = environment(ob)))
                               env = obj_info["env"];

                        while (objectp(env) && ! env->is_room())
                                env = environment(env);
                        room = env;
                        if (! objectp(room)) {
                                alloc_task(obj_info["file"], i);
                                return locate_ob(me, arg);
                        }
                        city = LOOK_CMD->locate(base_name(room));
                        coor_there=query("coor", room);
                        if (! coor_there)
                                return "◇" + obj_info["name"] + "◆婓珨跺源弇拸楊隅腔郖ㄛ拸楊刲扆﹝\n";

                        x_sub = coor_there["x"] - coor_here["x"];
                        y_sub = coor_there["y"] - coor_here["y"];
                        z_sub = coor_there["z"] - coor_here["z"];
                        dis = MIN(((x_sub + y_sub + z_sub) < 0 ? -(x_sub + y_sub + z_sub) :
                                (x_sub + y_sub + z_sub)) / CONSULT, 48);
                        if (z_sub == 0) alt = altitude[1];
                        else if (z_sub > 0) alt = altitude[0];
                        else alt = altitude[2];
                        if (x_sub > 0) x_sub = 1;
                        else if (x_sub < 0) x_sub = -1;
                        switch (x_sub) {
                        case 1 :
                                if (y_sub > 0) dir = directions[5];
                                else if (y_sub == 0) dir = directions[3];
                                else dir = directions[7];
                                break;
                        case 0 :
                                if (y_sub > 0) dir = directions[1];
                                else if (y_sub == 0) dir = directions[0];
                                else dir = directions[2];
                                break;
                        case -1:
                                if (y_sub > 0) dir = directions[6];
                                else if (y_sub == 0) dir = directions[4];
                                else dir = directions[8];
                                break;
                        }
                return display_locate(dis/2*2, alt, dir, city);
                }
        }
        return "";
}

string filter_symb(string fills, int flag)
{
        int i = random(2) + 1;
        int p;

        while (i--) {
                p = random(sizeof(fills));
                if (fills[p..p] != " ") {
                        i++;
                        continue;
                }
                if (p == (sizeof(fills) - 1) && fills[(p - 1)..(p - 1)] != " ") {
                        i++;
                        continue;
                }
                if (p == 0 && fills[(p + 1)..(p + 1)] != " ") {
                        i++;
                        continue;
                }
                if (fills[(p + 1)..(p + 1)] != " ") {
                        if (flag == 2) fills[(p - 1)..p] = colors[random(sizeof(colors))] + symbol[random(6) + 6] + NOR;
                        else fills[(p - 1)..p] = colors[random(sizeof(colors))] + symbol[random(3) + (flag * 3)] + NOR;
                } else {
                        if (flag == 2) fills[p..(p + 1)] = colors[random(sizeof(colors))] + symbol[random(6) + 6] + NOR;
                        else fills[p..(p + 1)] = colors[random(sizeof(colors))] + symbol[random(3) + (flag * 3)] + NOR;
                }
        }

        return fills;
}

string display_locate(int dist, string alti, string dire, string city)
{
        string *msg = allocate(3);
        string color = colors[random(sizeof(colors))];
        string n_color = (colors - ({color}))[random(sizeof(colors - ({color})))];
        int space_f = (random(4) + 6) * 2;
        int space_b = (random(4) + 6) * 2;
        int i;
        string fill_f = sprintf("%"+ space_f + "s", " ");
        string fill_b = sprintf("%"+ space_b + "s", " ");
        string output;

        switch(dire) {
                case "笚峓" :
                        msg[0] = color + (random(3) == 0 ? "沉" : (random(2) == 0 ? "" : "\\\\")) + (random(3) == 0 ? "＿" : (random(2) == 0 ? "∥" : "﹤")) + (random(3) == 0 ? "沅" : (random(2) == 0 ? "ㄞ" : "//")) + NOR;
                        msg[1] = color + (random(3) == 0 ? "↘" : (random(2) == 0 ? "／" : "==")) + symbol[random(8) + 24] + (random(3) == 0 ? "↙" : (random(2) == 0 ? "／" : "==")) + NOR;
                        msg[2] = color + (random(3) == 0 ? "汪" : (random(2) == 0 ? "ㄞ" : "//")) + (random(3) == 0 ? "ˍ" : (random(2) == 0 ? "∣" : "﹣")) + (random(3) == 0 ? "沛" : (random(2) == 0 ? "" : "\\")) + NOR;
                        break;
                case "控源":
                        msg[0] = "  " + color + symbol[random(3)] + NOR + "  ";
                        msg[1] = "  " + color + (random(10) < 2 ? (random(2) == 0 ? "||" : "′") : symbol[random(8) + 24]) + NOR + "  ";
                        msg[2] = msg[1];
                        break;
                case "鰍源":
                        msg[0] = "  " + color + (random(10) < 2 ? (random(2) == 0 ? "||" : "′") : symbol[random(8) + 24]) + NOR + "  ";
                        msg[1] = msg[0];
                        msg[2] = "  " + color + symbol[random(3) + 3] + NOR + "  ";
                        break;
                case "陲源":
                        msg[0] = "      ";
                        msg[1] = random(10) < 2 ? (random(2) == 0 ? "==" : "／") : symbol[random(8) + 24];
                        msg[1] = color + msg[1] + msg[1] + NOR + symbol[random(3) + 9];
                        msg[2] = msg[0];
                        break;
                case "昹源":
                        msg[0] = "      ";
                        msg[1] = random(10) < 2 ? (random(2) == 0 ? "==" : "／") : symbol[random(8) + 24];
                        msg[1] = color + symbol[random(3) + 6] + msg[1] + msg[1] + NOR;
                        msg[2] = msg[0];
                        break;
                case "陲控源":
                        msg[0] = "   " + color + (random(4) == 0 ? symbol[12] : symbol[random(3)]) + NOR + " ";
                        msg[1] = color + (random(10) < 2 ? (random(2) == 0 ? "//" : "ㄞ") : symbol[random(8) + 24]) + NOR;
                        msg[2] = " " + msg[1] + "   ";
                        msg[1] = "  " + msg[1] + "  ";
                        break;
                case "昹控源":
                        msg[0] = " " + color + (random(4) == 0 ? symbol[15] : symbol[random(3)]) + NOR + "   ";
                        msg[1] = color + (random(10) < 2 ? (random(2) == 0 ? "\\\\" : "") : symbol[random(8) + 24]) + NOR;
                        msg[2] = "   " + msg[1] + " ";
                        msg[1] = "  " + msg[1] + "  ";
                        break;
                case "陲鰍源":
                        msg[0] = color + (random(10) < 2 ? (random(2) == 0 ? "\\\\" : "") : symbol[random(8) + 24]) + NOR;
                        msg[1] = "  " + msg[0] + "  ";
                        msg[0] = " " + msg[0] + "   ";
                        msg[2] = "   " + color + (random(4) == 0 ? symbol[13] : symbol[random(3) + 3]) + NOR + " ";
                        break;
                case "昹鰍源":
                        msg[0] = color + (random(10) < 2 ? (random(2) == 0 ? "//" : "ㄞ") : symbol[random(8) + 24]) + NOR;
                        msg[1] = "  " + msg[0] + "  ";
                        msg[0] = "   " + msg[0] + " ";
                        msg[2] = " " + color + (random(4) == 0 ? symbol[14] : symbol[random(3) + 3]) + NOR + "   ";
                        break;
        }
        i = random(4) + 2;
        // 狟醱岆補秪匼
        /**********************************************************/
        msg[0] = filter_symb(fill_f, 0) + sprintf("%" + i + "s", " ") + msg[0] + "   " + filter_symb(fill_b, 0);
        msg[1] = filter_symb(fill_f, 2) + sprintf("%" + i + "s", " ") + msg[1] + "   " + filter_symb(fill_b, 2);
        msg[2] = filter_symb(fill_f, 1) + sprintf("%" + i + "s", " ") + msg[2] + "   " + filter_symb(fill_b, 1);
        if (alti == "詢揭") msg[0] += " " + colors[random(sizeof(colors))] + alti + NOR;
        if (alti == "腴揭") msg[2] += " " + colors[random(sizeof(colors))] + alti + NOR;
        output = HIW "垀婓郖ㄩ" + city + "\n岩岩岩岩岩岩岩岩\n\n" NOR + msg[0] + "\n" + msg[1] + "\n" + msg[2] + "\n" NOR + n_color + "擒燭硌杅ㄩ" +
                //sprintf(color + "%'↓'" + dist + "s" + n_color + "%'←'" + (48-dist) + "s%d\n" NOR, "", "", dist);
                sprintf(NOR + color + "%'岩'" + (48-dist) + "s" + NOR + n_color + "%'岩'" + dist + "s%d\n" NOR, "", "", dist);
        //output = HIW "岩岩岩岩岩岩岩岩\n\n" NOR + msg[0] + "\n" + msg[1] + "\n" + msg[2] + "\n" NOR + n_color + "擒燭硌杅ㄩ" +
                //sprintf(color + "%'岩'" + dist + "s" + n_color + "%'岩'" + (48-dist) + "s\n" NOR, "", "");
        return output;
        /**********************************************************
        msg[0] = sprintf("%" + i + "s", " ") + msg[0];
        msg[1] = sprintf("%" + i + "s", " ") + msg[1];
        msg[2] = sprintf("%" + i + "s", " ") + msg[2];
        if(alti == "詢揭") msg[0] += " " + colors[random(sizeof(colors))] + alti + NOR;
        if(alti == "腴揭") msg[2] += " " + colors[random(sizeof(colors))] + alti + NOR;
        return implode(msg, "\n") + sprintf("\n擒燭硌杅ㄩ%d\n", dist);
        **********************************************************/
}


string ask_for_task(object me, string arg)
{
        object who = this_player();
        object *inv, ob;
        string type, msg, where, find;

        if (! me || ! who || ! arg) return 0;
        inv = all_inventory(me);
        if (! sizeof(inv)) return 0;
        if (type = query_temp("task/" + query("id", who), me))
        switch(type) {
                case "sell" :
                        msg = "祥岆佽賸鎘ㄛ猁腔趕珨謗酴踢闖斕﹝";
                        break;
                case "draw" :
                        msg =  RANK_D->query_respect(who) + "彆眒冪賒疑賸" +
                                query("task/draw", who)+"腔瑞劓芞憩鴃辦跤"+RANK_D->query_self(me)+"勘ㄐ";
                        break;
                case "find" :
                        msg="豢咂徹斕賸ㄛ鏽"+query("task/find", who)+"懂遙﹝";
                        break;
        }
        else
        {
                for(int i = 0; i < sizeof(inv); i++)
                        // if(filter_color(inv[i]->query("name")) == arg && ob = inv[i])
                        if( filter_color(query("name", inv[i])) == arg )
                        {
                                ob = inv[i];
                                break;
                        }
                if(!objectp(ob)) {
                        delete("inquiry/"+arg, me);
                        return 0;
                }
                switch (random(3)) {
                case 0 :
                        msg = "涴弇" + RANK_D->query_respect(who) + "彆堋砩堤珨謗酴踢腔趕ㄛ" +
                                RANK_D->query_self(me) + "堋砩參" + arg + "闖跤" +
                                RANK_D->query_respect(who) + "﹝";
                        set_temp("task/"+query("id", who), "sell", me);
                        break;
                case 1 :
                        where = explode(read_file(QUEST_LIST + "place"), "\n")[random(sizeof(explode(read_file(QUEST_LIST + "place"), "\n")))];
                        msg = RANK_D->query_self(me) + "準都砑腕善珨盟" + where[0..strsrch(where, "/")-1] +
                                where[strsrch(where, "/")+1..] + "瑞劓芞ㄛ彆" + RANK_D->query_respect(who) +
                                "夔賒珨盟懂ㄛ" + RANK_D->query_self(me) + "堋蔚" + arg + "崌迵" +
                                RANK_D->query_respect(who) + "﹝";
                        set_temp("task/"+query("id", who), "draw", me);
                        set("task/draw", where[strsrch(where,"/")+1..], who);
                        break;
                case 2 :
                        find = explode(read_file(QUEST_LIST + "find"), "\n")[random(sizeof(explode(read_file(QUEST_LIST + "find"), "\n")))];
                        msg = RANK_D->query_self(me) + "涴" + arg + "硐遙祥闖ㄛ猁遙腕趕ㄛ鏽" + find + "懂﹝";
                        set_temp("task/"+query("id", who), "find", me);
                        set("task/find", find, who);
                        break;
        }
    }
    return msg;
}

int accept_object(object who, object me, object obj)
{
        string msg, type;
        int gift;

        if (! who || !me || playerp(who)) return 0;
        type = query_temp("task/" + query("id", me), who);

        if (obj->is_character() || obj->is_item_make())
                return 0;
        if (type != "draw" && type != "find" && type != "sell")
                return 0;
        if (type == "draw") {
                if( query("id", obj) != "paper" || !query("draw/info", obj) || 
                    (objectp(query("draw/info", obj)) && filter_color((query("draw/info", obj))->short()) != query("task/draw", me)) || 
                    query("draw/content", obj) == "奻醱觴匐媎腔艘祥堤賒腔岆妦繫﹝\n"){
                        message_vision(CYN"$N"CYN"紶賸紶羹耋ㄩ扂猁腔岆"+query("task/draw", me)+
                        "腔瑞劓芞ㄛ斕涴岆妦繫陲昹ˋ\n",
                        who);
                        return 0;
                } else {
                        if( query("draw/content", obj)[8..9] == "呥"){
                                msg = "賒腔呥祥崋繫欴ㄛ筍";
                                gift = 6000;
                        } else {
                                msg = "賒腔鼏鼏汜ㄛ淏";
                                gift = 1200;
                        }
                        message_vision(CYN "$N" CYN "萸賸萸芛耋ㄩ" + msg + "岆扂猁腔陲昹﹝\n", who);
                        msg="籵徹杸"+query("name", who)+"賒"+query("task/draw", me)+"瑞劓腔徹最ㄛ";
                }
        } else
        if (type == "find") {
                if( filter_color(query("name", obj)) != query("task/find", me)){
                        message_vision(CYN "$N" CYN "艘賸珨桉$n耋ㄩ" + RANK_D->query_respect(me) + "斕讀渣賸勘ㄛ扂猁腔岆" +
                                query("task/find", me)+"ㄛ祥岆$nㄐ\n",who,obj);
                        return 0;
                } else {
                        message_vision(CYN "$N" CYN "豝牉艘賸艘$n耋ㄩ祥渣ㄛ祥渣ㄛ扂猁腔憩岆涴跺﹝\n", who, obj);
                        msg="籵徹峈"+query("name", who)+"扆梑"+query("task/find", me)+"腔徹最ㄛ";
                        gift = 8000;
                }
        } else {
                if( query("money_id", obj) != "gold" || obj->query_amount()<1){
                        message_vision(CYN "$N" CYN "湮汒耋ㄩ佽賸珨謗酴踢憩岆珨謗酴踢ㄛ煦瑭飲祥夔漪緇﹝\n", who);
                        return 0;
                } else {
                        if (obj->query_amount() > 1)
                                message_vision(CYN "$N" CYN "虷柁柁耋ㄩ" + RANK_D->query_respect(me) + "暫堋砩嗣跤ㄛ" + RANK_D->query_sele(who) + "衄祥彶眳燴﹝\n", who);
                        else
                                message_vision(CYN "$N" CYN "淏伎耋ㄩ鉣ㄛ煦恅祥船ㄛ憩岆涴跺杅﹝\n", who);
                        msg = 0;
                }
        }

        message_vision("$n諉徹賸$N腔" + obj->short() + "﹝\n", me, who);
        destruct(obj);
        if( sizeof(filter_array(all_inventory(who),(:query("task_ob", $1):))) )
                obj=filter_array(all_inventory(who),(:query("task_ob", $1):))[0];
        if (objectp(obj)) {
                message_vision("$N鏽堤" + obj->short() + "跤$n﹝\n", who, me);
                obj->move(me, 1);
                delete("inquiry/"+filter_color(query("name", obj)), who);
                delete_temp("override/accept_object", who);
                who->delete_override("die");
        } else
                message_vision(CYN "$N" CYN "瘐痸腔虷耋ㄩ涴弇" + RANK_D->query_respect(me) + "妗婓岆勤祥蛂ㄛ饒跺陲昹眒冪掩梗軗賸﹝\n");

        delete_temp("task/"+query("id", me), who);
        delete("task/draw", me);
        delete("task/find", me);
        if (objectp(obj))
                set("geter", me->name(1), obj);
        if (msg)
                GIFT_D->delay_bonus(me, ([
                        "promot"  : msg,
                        "exp"     : gift + random(gift / 10),
                        "pot"     : gift * 3/5 + random(gift * 3/50),
                        "mar"     : gift * 3/5 + random(gift * 3/50),
                        "score"   : gift/10 + random(gift/50),
                        "weiwang" : gift/15 + random(gift/75),
                ]));
        return -1;
}

int die(object me)
{
        object *invs;

        if (! me) return 0;

        invs = all_inventory(me);

        if (! sizeof(invs))
                return 0;

        for (int i = 0; i < sizeof(invs); i++)
        {
                if (query("task_ob", invs[i]) && query("inquiry/" + filter_color(query("name", invs[i]), me) )
                && stringp(me->query_last_damage_name()))
                        set("keeper_killer", me->query_last_damage_name(), invs[i]);
        }
        return 0;
}

int task_reward(object me, object who, object ob)
{
        int exp, pot, weiwang, mar, score, td;
        int gongxian = 0;
        int combat_exp;
        int task_count = query("task/count", me);
        string gift;
        object gift_ob;
        string msg;
        int task_times;

        td = time() / 86400;
        if( query("task/total_count", me) >= 300 && 
            query("task/which_day", me) == td )
        {
                tell_object(me, WHT "斕踏毞眒冪俇傖TASK昢閉徹藩寞隅腔癹秶賸﹝\n" NOR);
                destruct(ob);
                return 1;
        }

/*
        if( query("reborn/times", me) )
        {
                tell_object(me, WHT "蛌岍俙模拸楊籵徹酕TASK昢鳳腕蔣療﹝\n" NOR);
                destruct(ob);
                return 1;
        }
*/

        if (! who->is_character() ||
            // userp(who) || ! ob->query("task_ob") ||
            userp(who) || ob->is_item_make() ||
            query("owner", ob) != filter_color(query("name", who)))
                return 0;

        if( query("task/which_day", me) != td )
        {
                set("task/which_day", td, me);
                set("task/total_count", 0, me);
        }

        addn("task/total_count", 1, me);
        combat_exp=query("combat_exp", me);

        if (combat_exp < 10000)
                exp = 175 + random(200);
        else if (combat_exp < 128000)
                exp = 200 + random(300);
        else if(combat_exp < 1024000)
                exp = 260 + random(500);
        else if(combat_exp < 2400000)
                exp = 360 + random(600);
        else if(combat_exp < 3000000)
                exp = 400 + random(800);
        else if(combat_exp < 6800000)
                exp = 500 + random(1000);
        else
                exp = 5000 + random(2000);

        if( query("geter", ob) == me->name(1) )
                exp = (exp + task_count)*10;

        if( query("big_task", ob) ) exp*=10;
        task_times = "/adm/daemons/actiond"->query_action("task_reward");
        if (task_times) exp *= task_times;

        if (combat_exp > 50000000 && combat_exp < 200000000)
                pot = exp/2 + random(exp/4);
        else if (combat_exp >= 200000000)
                pot = exp/3 + random(exp/4);
        else
                pot = exp/2 + random(exp/3);

        weiwang = pot / 5;
        mar = pot / 2;
        score = pot / 3;
        if( query("family/family_name", me) )
                gongxian = pot / 4;

        /*
        addn("combat_exp", exp, me);
        addn("potential", pot, me);
        addn("score", score, me);
        addn("experience", mar, me);
        addn("weiwang", weiwang, me);
        */

        msg = WHT "籵徹峈" + filter_color(who->name()) + "扆隙" + filter_color(ob->name()) + "腔徹最" NOR;
        GIFT_D->delay_bonus(me, ([
                "promot"  : msg,
                "exp"     : exp,
                "pot"     : pot,
                "mar"     : mar,
                "score"   : score,
                "weiwang" : weiwang,
                "gongxian": gongxian,
        ]), 1);

        finish(ob, me);

        task_count %= 500;
        if (task_count == 0 && query("task/count", me) > 0) gift = ob12_list[random(sizeof(ob12_list))];
        else if (task_count == 400) gift = "/clone/goods/tianshi-charm";
        else if (task_count == 300) gift = ob11_list[random(sizeof(ob11_list))];
        else if (task_count == 250) gift = "/clone/gift/xuanhuang";
        else if (task_count == 200) gift = "/clone/tongren/tongren2";
        else if (task_count == 180) gift = ob9_list[random(sizeof(ob9_list))];
        else if (task_count == 160) gift = ob8_list[random(sizeof(ob8_list))];
        else if (task_count == 140) gift = ob7_list[random(sizeof(ob7_list))];
        else if (task_count == 120)  gift = ob6_list[random(sizeof(ob6_list))];
        else if (task_count == 100)  gift = "/clone/tongren/tongren1";
        else if (task_count == 80)  gift = ob4_list[random(sizeof(ob4_list))];
        else if (task_count == 60)  gift = ob3_list[random(sizeof(ob3_list))];
        else if (task_count == 40)  gift = ob2_list[random(sizeof(ob2_list))];
        else if (task_count == 20)  gift = ob1_list[random(sizeof(ob1_list))];

#ifdef DB_SAVE 
        if (MEMBER_D->is_valid_member(query("id", who))) 
        {
                // clear task count
                if( query("task/count", me) >= 2000 )
                        set("task/count", 0, me);
        }
        else
#endif
        {          
                // clear task count
                if( query("task/count", me) >= 1000 )
                        set("task/count", 0, me);
        }
        
        if (stringp(gift)) {
                gift_ob = new(gift);
                gift_ob->move(me, 1);
                message_vision(CYN "$N" CYN "峚虷耋ㄩ" + RANK_D->query_self(who) +
                        "涴爵衄珨"+(stringp(query("base_unit", gift_ob))?
                        query("base_unit", gift_ob):
                        query("unit", gift_ob))+query("name", gift_ob)+CYN+
                        "崌跤" + RANK_D->query_respect(me) + "眕桶郅砩﹝\n", who);
        }
        /*
        log_file("static/task", sprintf("%s %s蔚%s蝠跤%s腕善%s萸夔﹝\n",
                log_time(), me->name(), filter_color(ob->name()),
                filter_color(who->name()), chinese_number(pot)));
        */

        destruct(ob);
        return 1;
}


void finish(object ob, object me)
{
        string id=query("id", ob);

        for (int i = 0; i < sizeof(task_status); i++)
                if (id == task_status[i]["id"]) {
                        task_status[i]["flag"]=query("name", me)+"("+query("id", me)+")";
                        break;
                }
        if( query("keeper_killer", ob) == me->name(1) )
                addn("task/count", 0, me);
        else if( query("geter", ob) == me->name(1) )
                addn("task/count", 1, me);
}

object search_env(object env)
{
        object ob;
        if (member_array(base_name(env), keys(search_room)) == -1)
                return 0;
        if (random(SEARCH_TIMES) == 0) {
                if (! objectp(ob = find_object(TASK_OB_DIR + search_room[base_name(env)])))
                        ob = load_object(TASK_OB_DIR + search_room[base_name(env)]);
                map_delete(search_room, base_name(env));
                return ob;
        }
        return 0;
}
