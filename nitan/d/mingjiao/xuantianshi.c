// Room: /d/mingjiao/xuantianshi.c

inherit ROOM;

void create()
{
        set("short", "懸天石");
        set("long", @LONG
從石上遠眺，只見雲海蒼茫處，險絕萬巒生，崑崙一脈，逶迤千
裏，真一派大好江山。關於懸天石，還有許多傳説。相傳明教第三十
代教主〖風舞柳影〗阿娜(Doll)為解明教之難，捨身於此，明教一代
絕學『乾坤大挪移』從此失傳。許多後來之人於此憑弔，莫不泣淚，
但更多的是從此石跳(tiao)下，想尋找『乾坤大挪移』祕籍，卻從沒
有人能安然而歸。
LONG );
        set("exits", ([
                "down" : __DIR__"shanlu3",
        ]));
        set("item_desc", ([
                "doll" : "一個來自波斯總教的教主。\n",
        ]));

        set("outdoors", "mingjiao");
        setup();
}
void init()
{
        add_action("do_tiao","tiao");
}
int do_tiao(object me)
{
        me = this_player();
        message_vision("$N遲疑了片刻猛地向深淵跳下，人影越飄越小。\n", me);
        if (me->query_dex() > 25)
        {
                me->move(__DIR__"gudi1");
        }
        else if (me->query_dex() > 20)
        {
                me->move(__DIR__"gudi1");
                me->unconcious();
        }
        else
        {
                me->move(__DIR__"gudi1");
                me->die();
        }
        return 1;
}
