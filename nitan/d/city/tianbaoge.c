// This program is a part of NT MudLIB

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "天寶閣");
        set("long", @LONG
這裏專賣市坊中各種字畫和書籍刻本，其中還有不少是難得一見的
珍本，但由於因該店孫老闆經營不善而倒閉。在此之後揚州外的長樂幫
曾經租下過這個店面，但不知為何又搬走了。辛友清最近剛將此店買下，
店內目前還沒有僱用員工，只有老闆辛友清一人無精打采地守着，四周
書架子(shelf) 亂七八糟堆着一些卷軸，線訂本，給人一種雜亂無章的
感覺。
LONG );
        set("region", "yangzhou");
        set("exits", ([
                "south" : __DIR__"xidajie3",
        ]));

        set("objects", ([
                __DIR__"npc/bookboss" : 1,
        ]));

        set("no_fight", 1);
        set("no_sleep", 1);
        set("day_shop", 1);
        set("item_desc", ([
                "shelf"  : "書架上堆滿了書，有些已經翻得破破爛爛。\n",
        ]));

	set("coor/x", -30);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}