//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "樓道");
        set ("long", @LONG
你推門入內，拾級上樓，黑暗中聽得樓梯發出輕微的吱吱之聲，腳
下只覺虛浮浮的，甚不自在。到得樓頂，側耳靜聽，絕無半點聲息，朦
朧微光中見左首有門。
LONG);
        set("exits", ([ 
                "east" : __DIR__"kongwu1",
                "down" : __DIR__"loudi",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2090);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}