// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;

void create()
{
        //迷宮房間所繼承的物件的檔案名稱。
        set_inherit_room( ROOM );

        //唯一房間
        set_unique_room( ({
                "/maze/mausoleum/unique_room/goldman_room",
                "/maze/mausoleum/unique_room/goldman_room2",
                "/maze/mausoleum/unique_room/goldman_room3",
                "/maze/mausoleum/unique_room/goldman_room4",
        }) );

        //中心房間
        set_center_room("/maze/mausoleum/unique_room/king_room");

        set_lonely_create(1);

        set_maze_boxs(1);

        set_maze_traps(2);

        //迷宮的單邊長
        set_maze_long(10);

        //入口方向(出口在對面)
        set_entry_dir("west");

        //入口與區域的連接方向
        set_link_entry_dir("west");

        //入口與區域的連接檔案名
        set_link_entry_room(__DIR__"westgate");

        //出口與區域的連接方向
        set_link_exit_dir("east");

        //出口與區域的連接檔案名
        set_link_exit_room("/d/luoyang/wenmiao");


        //普通房間描述
        set_maze_room_short(HIY "秦陵內宮" NOR);

        set_maze_room_desc(@LONG
自己站在長長的白玉石階之底，石階直通向上方那六丈來高、十裡
來寬的巨大平台。仰頭望去，廣闊的黑色頂穹綴滿了千萬顆寶石、明珠，
光彩奪目，璀璨似星河，浩瀚如夜空，將四周照得一片皎皎明亮。在那
瑰麗的頂穹下方，赫然竟是一座拔地而起、連天入穹的雄偉宮城。那巍
峨壯麗的城樓殿宇，鉤心鬥角的流檐飛瓦，綿延雄矗于白玉石台上，如
泰山壓頂，竟比長安城樓還要氣勢磅礡、雄奇瑰麗！石階兩邊的廣場上，
密密麻麻竟全是列成方陣的兵俑。銅人、陶俑、石雕……交相陳雜，少
說也有幾萬之眾，軍姿雄壯，威風凜凜。廣場上，一條條銀帶蜿蜒交錯，
閃耀著炫目的光澤，就像是江河匯集，一齊朝東面一個白光閃閃的水池
流去。
LONG);

        //入口房間短描述
        set_entry_short(HIR "秦陵內宮入口" NOR);

        //入口房間描述
        set_entry_desc(@LONG
自己站在長長的白玉石階之底，石階直通向上方那六丈來高、十裡
來寬的巨大平台。仰頭望去，廣闊的黑色頂穹綴滿了千萬顆寶石、明珠，
光彩奪目，璀璨似星河，浩瀚如夜空，將四周照得一片皎皎明亮。在那
瑰麗的頂穹下方，赫然竟是一座拔地而起、連天入穹的雄偉宮城。那巍
峨壯麗的城樓殿宇，鉤心鬥角的流檐飛瓦，綿延雄矗于白玉石台上，如
泰山壓頂，竟比長安城樓還要氣勢磅礡、雄奇瑰麗！石階兩邊的廣場上，
密密麻麻竟全是列成方陣的兵俑。銅人、陶俑、石雕……交相陳雜，少
說也有幾萬之眾，軍姿雄壯，威風凜凜。廣場上，一條條銀帶蜿蜒交錯，
閃耀著炫目的光澤，就像是江河匯集，一齊朝東面一個白光閃閃的水池
流去。
LONG);

        //出口房間短描述
        set_exit_short(HIW "秦陵內宮出口" NOR);

        //出口房間描述
        set_exit_desc(@LONG
自己站在長長的白玉石階之底，石階直通向上方那六丈來高、十裡
來寬的巨大平台。仰頭望去，廣闊的黑色頂穹綴滿了千萬顆寶石、明珠，
光彩奪目，璀璨似星河，浩瀚如夜空，將四周照得一片皎皎明亮。在那
瑰麗的頂穹下方，赫然竟是一座拔地而起、連天入穹的雄偉宮城。那巍
峨壯麗的城樓殿宇，鉤心鬥角的流檐飛瓦，綿延雄矗于白玉石台上，如
泰山壓頂，竟比長安城樓還要氣勢磅礡、雄奇瑰麗！石階兩邊的廣場上，
密密麻麻竟全是列成方陣的兵俑。銅人、陶俑、石雕……交相陳雜，少
說也有幾萬之眾，軍姿雄壯，威風凜凜。廣場上，一條條銀帶蜿蜒交錯，
閃耀著炫目的光澤，就像是江河匯集，一齊朝東面一個白光閃閃的水池
流去。
LONG);
}
