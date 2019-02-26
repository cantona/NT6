inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，人來人往非常繁忙，不時地有人
騎着馬匆匆而過。大道兩旁有一些小貨攤，似乎是集市。北邊
通向揚州城。東南是一大片樹林。
LONG);
        set("outdoors", "sanbuguan");
        set("exits", ([
                "south" : __DIR__"wdroad2",
                "north" : "/d/city/dujiangqiao",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
