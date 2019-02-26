// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;
string openlock(string lock); // 外部調用開鎖函數
varargs void init_data(object s, string arg);   // 初始化物件數據
string get_result(string str1, string str2);

mapping unlock = ([
// 對應房間可開啟鎖的序列A-B-C-D(3412)
        "A" : "123",
        "B" : "23",
        "C" : "134",
        "D" : "12",
]);

void create()
{
        //迷宮房間所繼承的物件的檔案名稱。
        set_inherit_room( ROOM );

        //唯一房間
        set_unique_room( ({
                "/maze/mausoleum/unique_room/jiguan_a",
                "/maze/mausoleum/unique_room/jiguan_b",
                "/maze/mausoleum/unique_room/jiguan_c",
                "/maze/mausoleum/unique_room/jiguan_d",
        }) );

        //中心房間
        set_center_room("/maze/mausoleum/unique_room/enter");

        //迷宮房間裏的怪物。
        set_maze_npcs( ([
                "/maze/mausoleum/npc/jiangling": random(2),
                "/maze/mausoleum/npc/qianrenzhang": random(2),
                "/maze/mausoleum/npc/bairenzhang": 1,
                "/maze/mausoleum/npc/bingshi": 1,
                "/maze/mausoleum/npc/baozi": random(2),
                "/maze/mausoleum/npc/tiger": random(2),
                "/maze/mausoleum/npc/lions": random(2),
                "/maze/mausoleum/npc/ni": 1,
                "/maze/mausoleum/npc/mammoth": random(2),
        ]) );

        set_lonely_create(1);

        //set_maze_boxs(5);

        //set_maze_traps(8);

        set_npcs_rate(40); 

        //迷宮的單邊長
        set_maze_long(10);

        //入口方向(出口在對面)
        set_entry_dir("south");

        //出口與區域的連接方向
        set_link_exit_dir("north");

        //出口與區域的連接檔案名
        set_link_exit_room("/d/luoyang/wenmiao");

        //普通房間描述
        set_maze_room_short(HIY "秦陵外宮" NOR);

        set_maze_room_desc(@LONG
自己站在長長的白玉石階之底，石階直通向上方那六丈來高、十里
來寬的巨大平台。仰頭望去，廣闊的黑色頂穹綴滿了千萬顆寶石、明珠，
光彩奪目，璀璨似星河，浩瀚如夜空，將四周照得一片皎皎明亮。在那
瑰麗的頂穹下方，赫然竟是一座拔地而起、連天入穹的雄偉宮城。那巍
峨壯麗的城樓殿宇，鈎心鬥角的流檐飛瓦，綿延雄矗於白玉石台上，如
泰山壓頂，竟比長安城樓還要氣勢磅礴、雄奇瑰麗！石階兩邊的廣場上，
密密麻麻竟全是列成方陣的兵俑。銅人、陶俑、石雕……交相陳雜，少
説也有幾萬之眾，軍姿雄壯，威風凜凜。廣場上，一條條銀帶蜿蜒交錯，
閃耀着炫目的光澤，就像是江河彙集，一齊朝東面一個白光閃閃的水池
流去。
LONG);

        //入口房間短描述
        set_entry_short(HIR "秦陵外宮入口" NOR);

        //入口房間描述
        set_entry_desc(@LONG
自己站在長長的白玉石階之底，石階直通向上方那六丈來高、十里
來寬的巨大平台。仰頭望去，廣闊的黑色頂穹綴滿了千萬顆寶石、明珠，
光彩奪目，璀璨似星河，浩瀚如夜空，將四周照得一片皎皎明亮。在那
瑰麗的頂穹下方，赫然竟是一座拔地而起、連天入穹的雄偉宮城。那巍
峨壯麗的城樓殿宇，鈎心鬥角的流檐飛瓦，綿延雄矗於白玉石台上，如
泰山壓頂，竟比長安城樓還要氣勢磅礴、雄奇瑰麗！石階兩邊的廣場上，
密密麻麻竟全是列成方陣的兵俑。銅人、陶俑、石雕……交相陳雜，少
説也有幾萬之眾，軍姿雄壯，威風凜凜。廣場上，一條條銀帶蜿蜒交錯，
閃耀着炫目的光澤，就像是江河彙集，一齊朝東面一個白光閃閃的水池
流去。
LONG);

        //出口房間短描述
        set_exit_short(HIW "秦陵外宮出口" NOR);

        //出口房間描述
        set_exit_desc(@LONG
自己站在長長的白玉石階之底，石階直通向上方那六丈來高、十里
來寬的巨大平台。仰頭望去，廣闊的黑色頂穹綴滿了千萬顆寶石、明珠，
光彩奪目，璀璨似星河，浩瀚如夜空，將四周照得一片皎皎明亮。在那
瑰麗的頂穹下方，赫然竟是一座拔地而起、連天入穹的雄偉宮城。那巍
峨壯麗的城樓殿宇，鈎心鬥角的流檐飛瓦，綿延雄矗於白玉石台上，如
泰山壓頂，竟比長安城樓還要氣勢磅礴、雄奇瑰麗！石階兩邊的廣場上，
密密麻麻竟全是列成方陣的兵俑。銅人、陶俑、石雕……交相陳雜，少
説也有幾萬之眾，軍姿雄壯，威風凜凜。廣場上，一條條銀帶蜿蜒交錯，
閃耀着炫目的光澤，就像是江河彙集，一齊朝東面一個白光閃閃的水池
流去。
LONG);
        init_data();
}

// 外部調用此函數傳遞參數lock為: "A"-"D"
string openlock(object me, string lock)
{
        string opened, str_want_open;
        mixed result;
        int i;
        object s;
        string file;

        if( !stringp(query("lock/opened")) || query("lock/opened") == "" ) {
              set("lock/opened", unlock[lock]);
              return unlock[lock];
        }

        str_want_open = unlock[lock];
        opened = query("lock/opened");

        if (! stringp(opened))
              return "erros: opened is not a string.\n";

        result = get_result(opened, str_want_open);
        if( sizeof(result) == 4 && result == "3412" ) {
                file = FUBEN_D->query_maze_dir(me);
                set("lock/unlocked", 1);
                set("lock/opened", result);
                switch( TIME_D->realtime_digital_clock()[0..3] )
                {
                case "上午" :
                case "中午" :
                        if( !s = find_object(file + "southgate"))
                                s = load_object(file + "southgate");

                        set("exits/north", file+"maze2/entry", s);
                        break;
                case "下午" :
                        if( !s = find_object(file + "westgate"))
                                s = load_object(file + "westgate");

                        set("exits/east", file+"maze3/entry", s);
                        break;
                case "晚上" :
                        if( !s = find_object(file + "northgate"))
                                s = load_object(file + "northgate");

                        set("exits/south", file+"maze4/entry", s);
                        break;
                case "凌晨" :
                        if( !s = find_object(file + "eastgate"))
                                s = load_object(file + "eastgate");

                        set("exits/west", file+"maze1/entry", s);
                        break;
                default :
                        break;
                }

                tell_room(s, HIG "只聽得轟隆隆幾聲，石門已陷入地下，露出了山洞的入口。\n" NOR);
                call_out("init_data", 180 + random(10), s, "enter"); // 三分鐘後重新初始化所有數據
                return "UNLOCKED";
        }
        set("lock/opened", result);

        remove_call_out("init_data");

        return query("lock/opened");

}

varargs void init_data(object s, string arg)
{
        string* rn = ({ "A", "B", "C", "D" });
        int ran_num;

        // 隨機分配房間參數，每次建立副本後順序都不一樣
        // 初試化個房間數據，各個房間數據統一交該物件管理，便於統一
        // 增加了解迷的難度
        ran_num = random(4);
        set("number/lockroom1", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        ran_num = random(3);
        set("number/lockroom2", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        ran_num = random(2);
        set("number/lockroom3", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        set("number/lockroom4", rn[0]);

        set("lock/unlocked", 0); // 所有鎖是否解開
        set("lock/opened", "");  // 已經打開的鎖序列

        if( objectp(s) && arg == "enter" ) {
                tell_room(s, HIG "只聽得轟隆隆幾聲，石門升起將山洞封住了。\n" NOR);
                delete("exits/west", s);
                delete("exits/east", s);
                delete("exits/south", s);
                delete("exits/north", s);
        }

        return;

}

string get_result(string str1, string str2)
{
        int n1, n2;
        string temp;

        if( !strcmp(str1, str2) ) return "";

        temp = "";

        for( n1=0; n1<sizeof(str1); n1++ ) {
                for( n2=0; n2<sizeof(str2); n2++ ) {
                      if( str2[n2..n2] == str1[n1..n1] )
                              temp += str2[n2..n2];
                }
        }

        if( temp == "" ) return str1 + str2;

        for( n1=0; n1<sizeof(temp); n1++ )
        {
                str1 = replace_string(str1, temp[n1..n1], "");
                str2 = replace_string(str2, temp[n1..n1], "");
        }

        return str1 + str2;
}
