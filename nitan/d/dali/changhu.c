//Room: /d/dali/changhu.c
//Date: June. 29 1998 by Java

inherit BUILD_ROOM;
void create()
{
        set("short","長湖");
        set("long", @LONG
長湖，周長約十余裡，湖面呈狹長形，故名。在密密的叢林中。
它宛如一彎新月，在藍天中輝耀。湖周鬆柏成林，蒼翠欲滴，芳草萋
萋，色鮮葉嫩，間有山花，點綴其間。湖水碧綠，似一幅在微風中抖
動的錦緞，綠的晶瑩，綠的活躍，綠的醉人。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "southdown"  : "/d/dali/shilin",
            "west"       : "/d/dali/shilin1",
            "northeast"  : "/d/dali/shilin2",
            "enter"      : "/d/dali/hole",
        ]));
        set("max_room",8);
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6800);
	set("coor/z", 30);
	setup();
}