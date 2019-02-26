// Room: /d/wuyi/tianyouguan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "天遊觀");
        set("long", @LONG
天遊峯的天遊觀，始建天牀，明嘉靖五年重建，有殿宇式的樓閣，
名「遨遊霄漢」，成為遊客飲茶，賞景的場所，閣後有妙高台、振衣崗
、紅豆樹諸勝。古人云：「飛泉響落睛疑雨，古木濃蔭夏亦寒」。
    觀中供奉着彭祖的兩個兒子：彭武和彭夷。相傳二人疏浚三三水，
堆就六六峯，才有了這座碧水丹山的人間洞天。山因之名。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "down"    : __DIR__"tianyoufeng",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -4970);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}
