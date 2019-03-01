// Room: /d/huanggong/zhonghedian.c

inherit ROOM;

void create()
{
        set("short", "中和殿");
        set("long", @LONG
碉欄玉砌, 金玉堂皇, 這才是皇族氣范. 飛檐敞椽, 支撐天地的大
柱正是八部天龍. 這裡是紫禁三殿的--中和殿.
    中和取意不偏不倚, 就是說凡事要恰如其份. 這座四角攢尖頂亭式
建築是皇帝到太和殿參加大典前休息準備和演習禮儀的地方. 每年春播
之季, 皇帝在此閱看種子和農具, 以示殷意. 
LONG
        );
        set("exits", ([
                "north" : __DIR__"baohedian",
                "south" : __DIR__"taihedian",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}