// Room: /d/qilian/tieshishan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        object ob;
        set("short", "鐵石山");
        set("long", @LONG
這裏是祁連山以西四十里處，山勢崢嶙，通山一色漆黑，光禿禿的
沒有一點生氣。遍山盡是鍩石，其色如墨，火燒成鐵，制器極剛利。從
這再往西走，就進入北祁連山區了。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "east"      : __DIR__"qilianshan",
                "west"      : __DIR__"zibaipo",
                "northwest" : __DIR__"ailaoshan",
        ]));
        set("objects", ([
//                __DIR__"obj/ironstone" : random(2),
        ]));
        set("coor/x", -13000);
        set("coor/y", 3000);
        set("coor/z", 100);
        setup();
//        replace_program(ROOM);
/*
  ob = new(__DIR__"obj/ironstone");
        if (ob->violate_unique())
        destruct(ob);
        else
        ob->move(this_object());
*/
}