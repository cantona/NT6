// /d/shenlong/kongdi.c
// Last Modified by winder on Aug. 18 2002

inherit ROOM;
string* npcs = ({
        __DIR__"npc/boy",
        __DIR__"npc/boy2",
        __DIR__"npc/boy3",
        __DIR__"npc/boy4",
        __DIR__"npc/girl",
});
 
void create()
{
        set("short", "空地");
        set("long",@LONG
這是一片長滿亂草的空地，四周都是亂石，雜草叢生。北邊是後山
山路，東邊有一間小屋，南面是深深的灌木林，西面是一片草坪。
LONG);
        set("exits", ([
                "west"    : __DIR__"caoping",
                "east"    : __DIR__"caodi",
                "southup" : __DIR__"lin2",
                "northup" : __DIR__"houshan",
        ]) );

        set("objects", ([
                CLASS_D("shenlong")+"/xu": 1,
                npcs[random(sizeof(npcs))] : random(2),
                npcs[random(sizeof(npcs))] : random(2),
                npcs[random(sizeof(npcs))] : random(2),
                npcs[random(sizeof(npcs))] : random(2),
                npcs[random(sizeof(npcs))] : random(2),
        ]) );
        set("outdoors", "shenlong");
        set("coor/x", 4000);
        set("coor/y", 3030);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
