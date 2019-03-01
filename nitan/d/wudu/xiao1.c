inherit ROOM;

void create()
{
        set("short", "江邊小路");
        set("long", @LONG
這裡是桃花江邊的一條泥土小路，一旁就是清澈的江水。夾岸連
綿不斷的桃花燦若雲霞，暗香襲人，引來許多蜜蜂在花樹間飛舞。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"xiao2",
                "north" : __DIR__"jiang2",
        ]));

        setup();
        replace_program(ROOM);
}