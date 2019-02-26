// Room: /d/songshan/shuyuan.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "嵩陽書院");
        set("long", @LONG
這裏原是嵩陽寺。現在文化昌明瞭，就改成了嵩陽書院，和睢陽書
院，嶽麓書院，白鹿書院合稱天下“四大書院”。北宋程顥程頤曾在此
講學。院內有古柏三株，漢武帝巡遊至此，冊封為大將軍，二將軍，三
將軍。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shandao2",
                "northwest" : __DIR__"shandao3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 770);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}