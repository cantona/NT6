inherit SHOP;

void create()
{
        set("short", "英雄樓");
        set("long", @LONG
英雄樓本是佛山鎮鳳天南所開，現在卻已經張羅給了別人。
整個店堂金碧輝煌，珠光寶器映得滿堂生輝。不過店裏的貨櫃
上卻空無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
英雄樓本是佛山鎮鳳天南所開，現在卻已經張羅給了別人。
整個店堂金碧輝煌，珠光寶器映得滿堂生輝。鋪里人來人往川
流不息。店鋪夥計正招呼着客人，忙得滿頭大汗。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/foshan/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__ "waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}