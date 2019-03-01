// Room: /d/yanziwu/path4.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "茶花小徑");
        set("long", @LONG
你走在蔓陀山莊中的綠泥小徑上。小徑兩側擺滿拉一盆盆茶花，結
了許許多多的五色茶花，時有蜂飛蝶舞戲弄花間。往北望前面有個精美
的小樓。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"garden",
                "south"  : __DIR__"path3",
        ]));
        set("coor/x", 1230);
        set("coor/y", -1280);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}