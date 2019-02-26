// void.c (re-created after Elon screwed it up on 07-24-95)

inherit ROOM;
int is_chat_room() {return 1;}
void create()
{
        set("short","最後樂園");
        set("long",@LONG        
這裏就是傳説中的 VOID -- 大神和巫師的最後樂園. 你看到四周一片
白茫茫的, 不一會從虛無中冒出一隻企鵝, 遞給你一罐「可口可樂」(tm), 
然後站在一旁很邪惡地笑著. 又過了一會, 一隻北極熊走了過來, 一掌拍扁
了那隻企鵝並從你手上搶走那瓶可樂, 大笑三聲後就從你眼前消失了.
你搖搖頭, 這種地方還是不要待太久的好.
LONG
        );

        set("exits", ([
                "down" : "/d/city/zuixianlou",
        ]));

        setup();
}

/*
void init()
{
        object me = this_player();
        if (!wizardp(me)) me->move("/d/city/zuixianlou");
        return;
}
*/

void init()
{
        object me;
        me=this_player();
        if (!wizardp(me)) me->save();
        return;
}