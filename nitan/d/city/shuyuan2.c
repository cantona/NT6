//Room: /d/city/shuyuan2.c

#define STORY_TOC "/doc/legend/toc"
inherit ROOM;

void create()
{
        set("short", "書院書庫");
        set("long", @LONG
這裡是書院的圖書館，窗明幾凈，一塵不染。壁上的書架 (shel
f)堆滿俠客行的先賢們的文選，記錄了俠客行的風風雨雨和無數凄婉
的、遙遠磨滅不去的傳說。你可以閱讀(read)到這些古老的故事。
LONG );
        set("item_desc", ([
            "shelf" : "此處已經被衙門查封了。\n",
        ]));
        set("objects", ([
                "/d/room/roomnpc/teagirl":1,
        ]));
        set("exits", ([
            "down" : "/d/city/shuyuan",
        ]));
	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
}