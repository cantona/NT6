//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "樓底");
        set ("long", @LONG
一座兩層小樓，四周有低矮的圍牆，牆內種了幾株柳樹。二樓的窗
檻上放了一盆黃色薔薇，只是三朵花兒都已萎謝，一陣風吹過，凋零的
花瓣便散落飄飛，忽而一對燕子吱啞飛過，感覺真有說不出的凄涼。小
門內光線昏暗，但仍看得見屋角有窄小的樓梯。
LONG);

        set("exits", ([ 
                "up"   : __DIR__"loudao",
                "east" : __DIR__"huayuan",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}