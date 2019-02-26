// garden.c

inherit ROOM;
void create()
{
        set("short","花園");
        set("long",@LONG
這是松風觀後的一個園子，庭院清幽，異種花卉甚是不少。此處高寒
花卉也異平常，風姿倬約，煞是惹人憐愛。東面通往掌門人卧室，南面是
三清殿。
LONG);
        set("exits",([
                "east"      : __DIR__"woshi",
                "south"     : __DIR__"songfengguan",
        ]));
        set("outdoors", "qingcheng");
        set("no_clean_up", 0);
        set("coor/x", -8080);
        set("coor/y", -820);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
 