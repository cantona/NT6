// Room: /yangzhou/chuitai.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "吹台");
        set("long", @LONG
吹台俗稱釣魚台，在綠蔭館西伸向湖心長渚盡頭。亭台三面臨湖，
與五亭橋、白塔隔湖相望，相傳乾隆皇帝曾在此垂釣。亭為四方，重檐
鬥角黃牆，板瓦頂，面東裝木刻縷空落地罩閣門，下置短欄。瀕湖三面
各開圓洞門。面吹台偏北而立，視西側圓門，景收五亭橋；看南側洞門，
映白塔高聳。以門借景，昔有"三星拱照"之稱。內懸“吹台”匾，外則
懸“釣魚台”匾。敞門兩側懸掛楹聯(lian)。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIC"
        浩        把
        歌        釣
        向        待
        蘭        秋
        渚        風
\n"NOR
        ]));
        set("exits", ([
                "east"  : __DIR__"pingtai2",
                "south" : __DIR__"balongqiao",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 130);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}