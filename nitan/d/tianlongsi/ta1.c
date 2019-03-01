inherit ROOM;

void create()
{
        set("short", "舍利塔");
        set("long", @LONG
這是天龍三塔中最高的一座，高約三百餘尺，共有十六級。相傳
塔頂原本供奉着一顆前代高僧的舍利子，但在當年奸臣楊義貞弒上德
帝篡位以至天下大亂時，舍利子不知何因而失蹤了，這也成為天龍寺
歷代主持的心腹大事。這個傳言也不知是真是假。
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
                "south" : __DIR__"baodian",
                "east" : __DIR__"wuwoge",
                "west" : __DIR__"wujingge",
                "north" : __DIR__"talin",
//                "up" :__DIR__"floor1",
        ]));
        set("objects",([
                __DIR__"npc/hutaseng1" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}