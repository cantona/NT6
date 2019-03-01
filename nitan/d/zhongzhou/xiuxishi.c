inherit ROOM;

void create()
{
        set("short", "旁廳");
        set("long", @LONG
一個小小的休息室，沒什麼東西。你走到這裡只想躺下好
好休息一下。床頭櫃上有小二沏好的濃茶。
LONG);
        set("exits", ([
                "east" : __DIR__"yinghaoup",
                
        ]));
        set("coor/x", -9040);
	set("coor/y", -990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}