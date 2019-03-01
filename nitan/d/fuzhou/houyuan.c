// room: houyuan.c
#include <room.h>

inherit ROOM;
int do_break(string arg);
int look_tai(string arg);

void create()
{
        set("short", "老宅後院");
        set("long", @LONG
這裡是向陽老宅的後院。滿地是發出朽爛霉氣的落葉。院子的中央
有一口井，井台(tai) 上刻著些字。院子南面有一扇門(men)，但已被坍
塌的磚瓦擋住了。
LONG );
        set("exits", ([
                "down" : __DIR__"well",
        ]));
        set("item_desc", ([
                "men" : "這扇門已被擋住無法通行，除非你打破(break)它。\n",
                "tai" : (:look_tai:),
        ]) );
        set("no_clean_up", 0);
        set("coor/x", 1820);
        set("coor/y", -6310);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_break", "break");
        add_action("look_tai", "look");
}

int do_break(string arg)
{
        int n;
        n=query("neili", this_player());
        if( !arg || arg!="men" ) {
                write("不要隨便打碎別人的東西！\n");
                return 1;
        }
        message_vision(
"$N走到後門前，拜出騎馬蹲襠式，深吸一口氣，雙掌同時拍出。\n", this_player());
        
        if (n>=200) {
            message_vision(
            "$N只聽一聲轟響，$N把門震開了！\n", this_player());
            set("exits/south", __DIR__"laozhai");
            set("neili", n-200, this_player());
            remove_call_out("close");
            call_out("close", 5, this_object());
        }
        else {
            message_vision(
"$N大吼一聲“開！”，結果什麼也沒發生。看來$N的內力不夠強。\n", this_player());
            set("neili", 0, this_player());
        }
        return 1;
}

void close(object room)
{
        message("vision","門上的磚頭瓦塊稀裡花拉坍塌下來，又擋住了小門。\n", room);
        delete("exits/south", room);
}

int look_tai(string arg)
{
        if( !arg || arg!="tai" ) return 0;
        write("井台上胡亂刻著許多臟話，其中一條是：\n");
        switch (random(15)) {
        case 0:
          write("林家沒一個好東西，我×林遠圖林震南林平之的祖宗！\n");
          break;
        case 1:
          write("有了密碼我就按，ＰＲＥＳＳ，按死這些龜兒子！\n");
          break;
        case 2:
          write("林平之這個小白臉生得有趣，大爺我真想把他當兔爺兒養起來。\n");
          break;
        case 3:
          write(this_player()->name()+"長得太醜了，大爺我看著一點兒性欲也沒有。\n");
          break;
        case 4:
          write("你們這些人在別人家的井台上亂塗臟話，太不像話了！\n");
          break;
        case 5:
          write("嘿，孫子，老爺我罵的就是你！\n");
          break;
        case 6:
          write("ＧＯ　ＡＨＥＡＤ，　ＡＮＤ　ＭＡＫＥ　ＭＹ　ＤＡＹ！\n");
          break;
        case 7:
          write("我雖生為男身，可我好想當女人呦！\n");
          break;
        case 8:
          write("ｆｕｃｋ　ｙｏｕ，　ｍａｎ！\n");
          break;
        case 9:
          write("井裡黑乎乎的，又沒火照明，正好讓我跟"+this_player()->name()+"快活快活！\n");
          break;
        case 10:
          write("說我下流，流到你家炕上了？！\n");
          break;
        case 11:
          write(this_player()->name()+"和翠花兩個人瞎搞！\n");
          break;
        case 12:
          write("儂迭只老屁眼！\n");
          break;
        case 13:
          write("ｗｏ　ｃａｏ　ｎｉ　ｍａ　ｇｅ　ｂｉ ！\n");
          break;
        case 14:
          write("我丟你老某！\n");
          break;
        }
        return 1;
}