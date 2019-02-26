// Room: /d/hangzhou/xihu.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西湖");
        set("long",@LONG
西湖之仙姿麗質，引無數騷人墨客淺吟低唱：“未能拋得杭州去，
一半勾留是西湖”。孤山峙立湖面，如一朵綠色花冠。蘇堤、白堤如兩
條綠緞，飄逸於湛湛碧水之中。湖中三島象三座海上仙山，鼎立湖心。
遠望山巒，雲山逶迤，霧靄漫漫。近觀湖水，微波盪漾，波光粼粼。湖
邊繁花如錦，綠蔭中亭台樓榭時隱時現。
    蘇子詩云：“水光瀲灩晴方好，山色空朦雨亦奇，欲把西湖比西子，
淡粧濃抹總相宜。”
LONG );
        set("outdoors", "xihu");
        set("no_clean_up", 0);
        set("coor/x", 4120);
        set("coor/y", -1440);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}