// room: /d/xingxiu/shashan.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "鳴沙山");
        set("long", @LONG
這是一座黃沙堆積形成的高數十丈的沙山。山峰陡峭，勢如刀刃。
微風吹動，沙山發出嗡嗡的響聲。故而當地人稱之為鳴沙山。此山北麓
有月牙泉。登山俯瞰，沙丘林立，清泉盪漾。從山頂下滑沙礫隨人體下
墜，鳴聲不絕于耳，興味盎然。故稱“沙嶺晴鳴”。
    沙土中似乎有一種蟲子在蠕動。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "northdown" : __DIR__"yueerquan",
                "eastdown"  : __DIR__"silk3",
                "west"      : __DIR__"wanxiangdong",
        ]));
        set("objects", ([
                __DIR__"npc/shachong" : 1
        ]));
        set("coor/x", -20320);
        set("coor/y", 200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}