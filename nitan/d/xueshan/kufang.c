inherit ROOM;

void create()
{
        set("short", "庫房");
        set("long", @LONG
這裏是練武場旁邊的小庫房，房裏密不通風，只有一絲光線從屋
檐小縫中投射進來。房中有些備用的武器，都是雪山弟子日常練功需
要用到的兵器。
LONG );
        set("exits", ([
                "east" : __DIR__"chang",
        ]));
        set("objects", ([
                "/clone/weapon/zhujian" : random(2),
                "/clone/weapon/gangdao" : random(2),
                __DIR__"obj/mugun" : random(2),
                __DIR__"obj/falun" : random(2),
        ]));
        setup();
}