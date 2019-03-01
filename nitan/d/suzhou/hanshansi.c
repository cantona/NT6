// Room: /d/suzhou/hanshansi.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "寒山寺");
        set("long", @LONG
你走出西門約三十裡地，就到了楓橋鎮，在唐元和年間，有高僧寒
山子曾來此居住，後希遷禪師在此建寺院時，更名寒山寺。唐開元年間，
詩人張繼赴京應試落第，返途舟船停靠楓橋，賦詩一首：“月落烏啼霜
滿天，江楓漁火對愁眠，姑蘇城外寒山寺，夜半歌聲到客船”。從此，
詩韻鐘聲，膾炙人口，寺因詩而名揚天下。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "southeast" : __DIR__"road4",
                "enter"     : __DIR__"zhengdian",
        ]));
	set("coor/x", 1040);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}