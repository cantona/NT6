// /guanwai/baiyun.c

inherit ROOM;

void create()
{
        set("short", "白雲峰");
        set("long", @LONG
白雲峰在天池之西，鹿鳴峰之南，為長白山主峰。山峰圓而高大，臨天
池而聳立，巍峨磅礡，如一口寶劍直插雲天。天氣晴好，天池十六峰畢露，
惟獨此峰常有煙雲繚繞，終日不散。古人有“看罷歸來回首顧，白山依舊白
雲封”的讚語。登臨此峰，誠有飄飄欲仙之感。
LONG );
        set("exits", ([
                "north"      : __DIR__"luming",
                "eastdown"   : __DIR__"tianchi1",
                "southwest"  : __DIR__"yuzhu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}