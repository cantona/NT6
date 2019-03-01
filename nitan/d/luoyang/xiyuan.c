inherit ROOM;

void create()
{
        set("short", "京韻大戲院");
        set("long", @LONG
戲院內有一座高高的戲台，台上一些臉上上過妝的人，穿著戲服，拿
著道具，正手舞足蹈，咿咿呀呀的唱著中國的國粹京劇，台下有好幾排椅
子，坐滿了戲迷，票友，正興致勃勃的看著台上的表演，聽到妙處，會忍
不住站起來，大叫一聲“好”！
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"houtai",
                  "west" : __DIR__"sroad4",
        ]));
        set("objects", ([
                "/d/beijing/npc/guanzhong" : 4,
                "/d/beijing/npc/xizi2" : 1,
                "/d/beijing/npc/xizi3" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}