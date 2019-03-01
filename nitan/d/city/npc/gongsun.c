// gongsun.c

inherit NPC;

string apply_dancer(object me);
string answer_leaving(object me);
int do_yes(string arg);
void do_something();

void create()
{
        set_name("公孫大娘", ({"gongsun daniang", "gongsun", "daniang"}));
        set("age", 32);
        set("gender", "女性");
        set("per", 20);
        set("long","城內不知道公孫大娘的人恐怕沒幾個。\n特別是那些文人騷客，跟公孫大娘不熟簡直就是沒面子。\n");
        set("title", "老板娘");
        set("attitude", "friendly");

        set("combat_exp", 40000);
        set("max_force", 400);
        set("force", 400);
        set("force_factor", 5);
        set_skill("unarmed", 60);
        set_skill("dodge", 90);
        set_skill("yueying-wubu", 120);
        set_skill("parry", 60);
        set_skill("literate", 90);
        set_skill("sword", 90);
        map_skill("dodge", "yunying-wubu");

        set("inquiry", ([
                "name" : "嘻嘻...連老娘我公孫大娘你都不知道...\n",
                "here" : "嘿嘿...天下美景不勝數，長安此處最繁華。\n",
                "舞妓" : (: apply_dancer :),
                "舞女" : (: apply_dancer :),
                "歌妓" : (: apply_dancer :),
                "歌女" : (: apply_dancer :),
                "leave" : (: answer_leaving :),
                "離開" : (: answer_leaving :),
        ]) );

        setup();
        carry_object(CLOTH_DIR"skirt")->wear();
        carry_object(CLOTH_DIR"shoes")->wear();
        add_money("silver", 200);
}

void do_something()
{
        command(sprintf("bet %d silver", 1+random(5)));
        call_out ("do_something", 120);        
}

string apply_dancer(object me)
{
        me=this_player();
        if( query("gender", me) == "男性" )
        {
                return "這就要看閣下的本事了，我可幫不上多少忙。\n";
        }
        else
        {
                if( query("class", me) == "dancer" )
                        return "好好幹吧，以後不愁嫁不上好人家。\n";

                if( query("age", me) >= 30 )
                        return "歲月不饒人，姑娘還是另尋它路吧。\n";

                message_vision("公孫大娘看了$N一眼嘆道：這碗飯可不是容易吃的。\n", me);        
                set_temp("dancer_applied", 1, me);
                return "姑娘果真是下了決心？(yes)\n";
        }
}

string answer_leaving(object me)
{
        me=this_player();
        if( query("gender", me) == "男性" )
        {
                return "快滾，滾得遠遠的！老娘這地方還怕沒人來嗎？\n";
        }
        else
        {
                if( query("class", me) == "dancer" )
                        return "既入此門，大家都知道了，離不離開又有什麼分別呢？\n";
                else return "快走吧，這裡本來就不是女人玩的地方。\n";
        }
}

void init()
{
        ::init();

        remove_call_out("do_something");
        call_out ("do_something", 120);                

        add_action("do_yes", "yes");
}

int do_yes(string arg)
{
        object me;

        me=this_player();
        
        if( query_temp("dancer_applied", me) )
        {
                message_vision("$N答道：我都想清楚了！\n\n", me);
                message_vision("公孫大娘拍了拍$N的頭道：好好幹！只要能碰上好運氣，榮華富貴垂手可得！\n", me);
                delete_temp("dancer_applied", me);
                set("class", "dancer", me);
                return 1;
        }

        return 0;
}
