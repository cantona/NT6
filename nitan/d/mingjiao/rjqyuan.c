//RJQYUAN.C

inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
你走進了鋭金旗的大院，卻發現這裏人影稀疏，雖聽見叮叮咚咚
的打鐵聲，卻見不到打鐵鋪，那聲音似乎是從深遠的地下傳來的。向
西走，就要進入門樓了。院子左首可能是練武場，隱約傳來打鬥聲；
右首是一座大廳，象是鋭金旗的議會場所。
LONG );
        set("exits", ([
                "west" : __DIR__"rjqmenlou1",
                "north" : __DIR__"rjqdating",
                "south" : __DIR__"rjqlwch",
                "out": __DIR__"rjqmen",
        ]));
/*
        set("objects",([
            CLASS_D("mingjiao")+"/lengqian":1,
            CLASS_D("mingjiao")+"/shuobude":1,
            CLASS_D("mingjiao")+"/zhangzhong":1,
            CLASS_D("mingjiao")+"/pengyingyu":1,
            CLASS_D("mingjiao")+"/zhoudian":1,
            CLASS_D("mingjiao")+"/yinyewang":1,
        ]));
*/
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}