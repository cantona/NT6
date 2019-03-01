//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{

        set ("short", "元妙觀");
        set ("long", @LONG
這裡原稱玄妙觀，建于唐開元年間，原來在荊州城西北，後遷至此。
為避康熙皇帝玄燁之名諱，將“玄”改為“元”。眼前一座四角攢尖頂
的三層樓閣是玉皇閣，後面是玄武殿，建在崇台之上，古樸雅致，巍峨
莊嚴。
LONG);
        set("exits", ([ 
                "north" : __DIR__"xxend",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -7080);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}