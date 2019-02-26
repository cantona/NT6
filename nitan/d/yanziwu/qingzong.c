//ROOM: /d/yanziwu/qingzong.c

inherit ROOM;
void create()
{
        set("short", "青冢");
        set("long", @LONG
你在竹林中七繞八繞，忽然豁然開朗，原來到了慕容世家的墓地，
據説燕子塢的主人就葬於此了。地上長滿了細的小草，傳説這種草常
年碧綠，永不枯萎。似乎除了向南有一片竹林外別無出口。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "south" : __DIR__"zhulin3",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}