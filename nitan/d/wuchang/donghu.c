//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "東湖");
        set ("long", @LONG
一面碧綠的湖水，浩淼連天，湖面煙波迷茫，一派江南好風景。
LONG);
        set("exits", ([
                "west" : __DIR__"huanghelou",
        ]));
  
        set("outdoors", "wuchang");
        set("no_clean_up", 0);
        set("coor/x", -1390);
        set("coor/y", -2220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}