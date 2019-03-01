// pigroom.c 拱豬房
// Written by Xiang Tu <tu@uwalpha.uwinnipeg.ca>

#include <pig.h>


inherit ROOM;

string         *seat = ({ "north", "west", "south", "east" });
mapping chinese_seat = ([ 
        "north": "北邊",
        "west" : "西邊",
        "south": "南邊",
        "east" : "東邊",
]);

int pig_stage;
int round_no, roundcard_count;
string *round_order = allocate(4);
int bid_flag;
string bidcard_str = "";
object server;
string claimer;
mapping        pl = allocate_mapping(4),
         cards = allocate_mapping(4),
        card_count = allocate_mapping(4),
        roundcards = allocate_mapping(4),
        picks = allocate_mapping(4),
        pick_count = allocate_mapping(4),
        passed = allocate_mapping(4),
        agreed = allocate_mapping(4),
        hscore = allocate_mapping(4),
        tscore = allocate_mapping(4);
        
string        dealer;
int        *allow_playbid = allocate(4);
int         *oldcards = allocate(52), 
        *newcards = allocate(52);

int pl_count();
void pig_init();
void deal_init();
void bid_init();
void after_bid();
void round_init(string w);
void after_round();
void play_init();
void after_claim();
void after_play();
void after_round();
void after_winner(string rw);
void after_hand();
void auto_play();

string refresh_str(string dir);
string picks_str();
string table_str(string dir);
string scoreboard_str();

void reset()        // set this room to no_reset
{}

int pl_count()
{
        int i, r;
        for (i = r = 0; i < 4; i++)
                if (objectp(pl[seat[i]]))
                        r++;
                else
                        map_delete(pl, seat[i]);
        return r;
}
void pig_init()
{
        int i;
        pig_stage = PIG_INITTING;
        for (i = 0; i < 4; i++) {
                tscore[seat[i]] = hscore[seat[i]] = 0;
                cards[seat[i]] = allocate(13);
                picks[seat[i]] = allocate(16);
        }
        for (i = 0; i < 52; i++)
                oldcards[i] = i;
}
void deal_init()
{
        pig_stage = PIG_DEALING;
        tell_room(this_object(), scoreboard_str());
        tell_room(this_object(),"桌長請 deal ！\n");
}
void bid_init()
{
        int i;
        pig_stage = PIG_BIDDING;
        bidcard_str = "";
        bid_flag = 0;
        for (i = 0; i < 4; i++) {
                allow_playbid[i] = 1;
                passed[seat[i]] = 0;
        }
}

void play_init()
{
        int i, j;
        pig_stage = PIG_PLAYING;
        round_no = 1;
        for (i = 0; i < 4; i++) {
                pick_count[seat[i]] = 0;
                card_count[seat[i]] = 13;
                for (j = 0; j < 16; j++)
                        picks[seat[i]][j] = 53;
                claimer = "";
                agreed[seat[i]] = 0;
        }
        round_init(dealer);
}
void round_init(string rw)
{
        int i;
        for (i = 0; i < 4; i++) 
                roundcards[seat[i]] = -1;
        roundcard_count = 0;
        round_order = PIG_D->order_turn(rw);
        if (pig_stage == PIG_PLAYING)
                tell_object(pl[rw], refresh_str(rw) + "現在輪到你出牌！\n");
}
        
void init()
{
        add_action("do_sit", "sit");
        add_action("do_leave", "leave");
        add_action("do_deal", "deal");
        add_action("do_bid", "bid");
        add_action("do_bid", "sell");
        add_action("do_pass", "pass");
        add_action("do_play", "play");
        add_action("do_refresh", "refresh");
        add_action("do_skip", "skip");
        add_action("do_claim", "claim");
}

string picks_str()
{
        int i;
        string r = "", t; 
        for (i = 0; i < 4; i++) {
                t = "";
                if (objectp(pl[seat[i]]))
                        t=query("name", pl[seat[i]]);
                else 
                        t = chinese_seat[seat[i]];
                if (pick_count[seat[i]] > 0) {
                        t += "撿了下面這些牌：\n";
                        t += PIG_D->refresh(picks[seat[i]], 0, pick_count[seat[i]] - 1);
                }
                else
                               t = "";
                r += t;
        }
        return r;
}

string refresh_str(string dir)
{
//        if (dir != "north" && dir != "west" && dir != "south" && dir != "east")
                return PIG_D->refresh(cards[dir], 0, card_count[dir] - 1);
//        return "";
}
        

string table_str(string dir)        // what's going on in table ?
{
        int i;
        mapping rseat = ([]);
        string r = "", z = "";

        if (pig_stage == PIG_PLAYING && pl_count() == 4) { // if in playing mode
                if (dir != "north" && dir != "west" && dir != "south" 
                        && dir != "east")
                        rseat = PIG_D->order_turn("north");
                else
                        rseat = PIG_D->order_turn(dir);
//                r = "桌上面正在激烈的拱着！！\n";
        
                if (roundcard_count < 4)
                        r = sprintf("現在是第%s輪，該由%s出牌。\n", 
                        chinese_number(round_no), 
                        query("name", pl[round_order[roundcard_count]]));
                if (bidcard_str != "")
                        r += "賣了的牌：" + bidcard_str + "\n\n";
                else
                        r += "沒有人賣牌。\n";
                r=sprintf("%s%24s（%s）\n",r,"",query("name", pl[rseat[2]]));//writesnorthname
                r = sprintf("%s%26s%s\n", r, "", 
                        PIG_D->card_str(roundcards[rseat[2]]));
                r = sprintf("%s%4s%16s%6s%6s%6s%s\n", r, "", "（" + 
                        query("name", pl[rseat[3]])+"）",
                        PIG_D->card_str(roundcards[rseat[3]]), "", 
                        PIG_D->card_str(roundcards[rseat[1]]), "（" +
                        query("name", pl[rseat[1]])+"）");
                r = sprintf("%s%26s%s\n", r, "",
                        PIG_D->card_str(roundcards[rseat[0]]));
                r=sprintf("%s%24s（%s）\n",r,"",query("name", pl[rseat[0]]));
                if (card_count[dir] > 0)
                        r += refresh_str(dir);
                r += picks_str();
        }
        else {
                r = "這是一張專門用於拱豬的四方桌。\n\n";
                       if (bidcard_str != "")
                        r += "賣了的牌：" + bidcard_str + "\n\n";
                else
                        r += "沒有人賣牌。\n";
                for (i = 0; i < 4; i++) 
                        if (objectp(pl[seat[i]])) {
                                if (pl[seat[i]] == server) z = "@"; else z = "";
                                r = sprintf("%s%s的椅子上坐的是：%s(%s)%s。\n", r,
                                chinese_seat[seat[i]],query("name", pl[seat[i]]),
                                query("id", pl[seat[i]]),z);
                        }
                        else
                                r = sprintf("%s%4s的椅子是空的。如果你想玩，可以用 sit %-5s 坐上去。\n",
                                r, chinese_seat[seat[i]], seat[i]);
        }
        return r;
}

string scoreboard_str()
{
        int i;
        string r;
        r = "拱豬成績表(Scoreboard)\n－－－－－－－－－－－－－－－－－\n姓名　　　　　　　　盤分　　　總分\n－－－－－－－－－－－－－－－－－\n";
        for (i = 0; i < 4; i++)
                if (objectp(pl[seat[i]]))
                        r = sprintf("%s%-14s%10d%10d\n", r,
                        query("name", pl[seat[i]]),
                        (int)hscore[seat[i]], (int)tscore[seat[i]]);
        return r + "－－－－－－－－－－－－－－－－－\n";
}

void score_reset()
{
        int i;
        for (i = 0; i < 4; i++)
                tscore[seat[i]] = 0;
}

int do_skip(string arg)
{
        if( !query_temp("pigging_seat", this_player()) )
                return notify_fail("你沒有在拱豬！\n");
        if (this_player() != server)
                return notify_fail("只有桌長才能跳過這副牌！\n");
        if (pig_stage < PIG_BIDDING)
                return notify_fail("牌都沒有，跳什麼？\n");
        message_vision("桌長$N決定跳過這副牌！！\n", server);
        if (pl_count() == 4)
                deal_init();
        return 1;
}

void after_claim()
{
        int i, j, k;
        for (i = 0; i < roundcard_count; i++) 
                if (PIG_D->is_special(roundcards[i]))
                        picks[claimer][pick_count[claimer]++] = roundcards[j];
        for (i = 0; i < 4; i++)
                for (j = 0; j < card_count[seat[i]]; j++)
                        if (PIG_D->is_special(cards[seat[i]][j]))
                                picks[claimer][pick_count[claimer]++] = cards[seat[i]][j];
        after_hand();
}
int do_claim(string arg)
{
        int i;
        object me = this_player();
        if( !query_temp("pigging_seat", me) )
                return notify_fail("你沒有在拱豬！\n");
        if (pl_count() != 4)
                return notify_fail("現在桌子上沒坐滿！\n");
        if (pig_stage != PIG_PLAYING)
                return notify_fail("你想幹什麼？\n");
        if( claimer == query_temp("pigging_seat", me) )
                return notify_fail("一次就夠了！\n");
        if (!arg) {
                if (claimer != "")
                        return notify_fail("claim yes|no ？\n");
                agreed[claimer=query_temp("pigging_seat", me)]=1;
                write("你發出全收的要求！等待迴音……\n");
                for (i = 0; i < 4; i++)
                        if (seat[i] != claimer)
                                tell_object(pl[seat[i]],query("name", me)+
                                        "認為他手中的牌都是大的了！\n" +
                                        refresh_str(query_temp("pigging_seat", me))+
                                        "請用 claim yes 通過，或者 claim no 否決。\n");
                return 1;
        }
        if (arg == "yes") {
                if (claimer == "")
                        return notify_fail("沒有人想全收！\n");
                if( !agreed[query_temp("pigging_seat", me)]){
                        agreed[query_temp("pigging_seat", me)]=1;
                        message_vision("$N同意$n的牌都是大的了！\n", me, pl[claimer]);
                        for (i = 0; i < 4; i++)
                                if (agreed[seat[i]] != 1)
                                        return 1;
                        message_vision("$N的要求被通過了！！\n", pl[claimer]);
                        after_claim();
                        return 1;
                }
        }
        if (arg == "no") {
                if (claimer == "")
                        return notify_fail("沒有人想全收！\n");
                message_vision("$N否決了$n的要求！！\n繼續出牌！\n", me, pl[claimer]);
                claimer = "";
                for (i = 0; i < 4; i++)
                        agreed[seat[i]] = 0;
                return 1;
        }
        else
                return notify_fail("claim 什麼？\n");
}
        

int do_sit(string arg)
{
        object me = this_player();

        if (!arg || (arg != "north" && arg != "west" && arg != "south" && arg != "east"))
                return notify_fail("你想坐在哪裏？\n");

        if (server == me)
                return notify_fail("桌長不能換坐位！\n");

        map_delete(pl,query_temp("pigging_seat", me));
                
        if (!objectp(pl[arg])) {
                if (!pl_count()) {
                        pig_init();
                        server = me;
                        write("你現在是桌長！\n");
                        round_order = PIG_D->order_turn(dealer = arg);
                }
                pl[arg] = me;
                set_temp("pigging_seat", arg, me);
                message_vision("$N坐上了" + chinese_seat[arg] + "的位子。\n", me);
                if (pl_count() == 3)
                        tell_room(this_object(), "現在是三缺一，你們只再需要一個玩家就可以開拱了！\n");
                if (pl_count() == 4) {
                        tell_room(this_object(), "好，人湊齊了！\n");
                        deal_init();
                }
                return 1;
        }
        else
                return notify_fail("這個位子上已經有人了！\n");
}

int do_leave(string arg)
{
        int i;
        object me = this_player();

        if (!query_temp("pigging_seat", me))
                return notify_fail("你現在沒有在拱豬！\n");
        else if (server == me) {
                message_vision("桌長$N不想再拱下去了！\n", me);
                server = 0;
                for (i = 0; i < 4; i++) 
                        if (objectp(pl[seat[i]])) {
                                message_vision("$N站了起來。\n", pl[seat[i]]);
                                delete_temp("pigging_seat", pl[seat[i]]);
                                map_delete(pl, seat[i]);
                        }
                pig_stage = PIG_INITTING;
                return 1;
        }
        else {
                map_delete(pl,query_temp("pigging_seat", me));
                delete_temp("pigging_seat", me);
                message_vision("$N不想再拱了，站了起來！\n", me);
                return 1;
        }
}

void do_assign_cards()        // assign cards to players
{
        int i, j, k = 0;

        for (i = 0; i < 13; i++)
                for (j = 0; j < 4; j++) 
                        cards[seat[j]][i] = newcards[k++];
        for (i = 0; i < 4; i++) {
                cards[seat[i]] = sort_array(cards[seat[i]], 1);
                tell_object(pl[seat[i]], PIG_D->refresh(cards[seat[i]], 0, 12));
                card_count[seat[i]] = 13;
        }
}

int do_deal(string arg)
{
        int i, j, k;
        object me = this_player();
        if (me != server)
                return notify_fail("你不是桌長！\n");
        if (pig_stage != PIG_DEALING || pl_count() != 4)
                return notify_fail("現在不能發牌！\n");
        PIG_D->shuffle(oldcards, newcards, 2);

        for (i = 0; i < 13; i++)
                for (j = 0; j < 4; j++) 
                        cards[seat[j]][i] = newcards[k++];
        for (i = 0; i < 4; i++) {
                cards[seat[i]] = sort_array(cards[seat[i]], 1);
                tell_object(pl[seat[i]], "你得到的牌為：\n" +
                        PIG_D->refresh(cards[seat[i]], 0, 12));
                card_count[seat[i]] = 13;
        }
        tell_room(this_object(), "發完牌了，有誰要賣牌的沒有？\n");
        tell_room(this_object(), "如果你賣完了牌，打一下 pass 。\n");
        bid_init();
        return 1;
}

int do_refresh(string arg)
{
        object me = this_player();
        if( !query_temp("pigging_seat", me) )
                return notify_fail("你沒有在拱豬！\n");
        if (pig_stage < PIG_BIDDING || 
                card_count[query_temp("pigging_seat", me)]<1 )
                return notify_fail("你手上沒有牌！\n");
        tell_object(pl[query_temp("pigging_seat", me)],
                "你手上有這些牌：\n"+refresh_str(query_temp("pigging_seat", me)));
        return 1;
}

int do_bid(string arg)
{
        object me = this_player();
        int c, b;
        string ts;

        if( !query_temp("pigging_seat", me) )
                return notify_fail("你沒有在拱豬！\n");
        if (pig_stage != PIG_BIDDING)
                return notify_fail("現在不是賣牌的時候！\n");
        if (!arg)
                return notify_fail("你想賣什麼？\n");
        if ((c = PIG_D->is_validcard(arg)) == -1 ||
                !PIG_D->has_card(cards[query_temp("pigging_seat", me)],0,12,c) )
                return notify_fail("你手上沒有這張牌！\n");
        if (!(b = PIG_D->is_validbid(c)))
                return notify_fail("這張牌不能被賣！\n");
        if (bid_flag & b)
                return notify_fail("這張牌已經被賣過了！\n");
        bid_flag |= b;
        switch (b) {
        case BID_SPIG :
                allow_playbid[0] = 0; break;
        case BID_HACE :
                allow_playbid[1] = 0; break;
        case BID_DSHEEP :
                allow_playbid[2] = 0; break;
        case BID_CTRANS :
                allow_playbid[3] = 0; break;
        }
        message_vision("$N説道：我賣" + PIG_D->card_str(c) + "！\n", me);
        ts = "";
        if (bidcard_str != "") ts = "，";
        bidcard_str=PIG_D->card_str(c)+"（"+query("name", me)+"）"+
                ts + bidcard_str;

        return 1;
}

int do_pass(string arg)
{
        object me = this_player();
        int i;

        if( !query_temp("pigging_seat", me) )
                return notify_fail("你沒有在拱豬！\n");
        if (pig_stage != PIG_BIDDING)
                return notify_fail("你想幹什麼？\n");
        if( passed[query_temp("pigging_seat", me)] == 1 )
                return notify_fail("你已經停賣了！\n");
        passed[query_temp("pigging_seat", me)]=1;
        message_vision("$N説道：我停賣！\n", me);
        for (i = 0; i < 4; i++) 
                if ((int)passed[seat[i]] == 0)
                        return 1;

        for (i = 0; i < 4; i++)
                passed[seat[i]] = 0;
        tell_room(this_object(), "全部停賣，開拱！！\n");
        tell_room(this_object(),"這把由"+query("name", pl[dealer])+"先出。\n");

        play_init();
        return 1;
}

void after_play()
{
        int i;
        roundcard_count++;
        for (i = 0; i < 4; i++) 
                if (card_count[seat[i]] > 0)
                        tell_object(pl[seat[i]], table_str(seat[i])); 
        if (roundcard_count > 3)
                after_round();
}
        
void after_winner(string rw)
{
        int i;
        message_vision("$N的" + PIG_D->card_str(roundcards[rw]) + "最大！\n", pl[rw]);
        for (i = 0; i < 4; i++)
                if (PIG_D->is_special(roundcards[seat[i]])) {
                        picks[rw][pick_count[rw]++] = 
                                roundcards[seat[i]];
                        if (roundcards[seat[i]] == SPIG) {
                                message_vision("$N得到了豬頭！！\n", pl[rw]);
                                dealer = rw;
                        }
                }
        picks[rw] = sort_array(picks[rw], 1);
}

void after_round()
{
        int i;
        string rw;

        allow_playbid[SUIT(roundcards[round_order[0]])] = 1;
        after_winner(rw = PIG_D->card_cmp4(roundcards, SUIT(roundcards[round_order[0]])));
        round_init(rw);
        
        if (round_no++ == 12) 
                auto_play();  // starts auto_play
}
void auto_play()
{
        int i;
        for (i = 0; i < 4; i++)
                roundcards[seat[i]] = cards[seat[i]][0];
        roundcard_count = 4;
        for (i = 0; i < 4; i++) {
                card_count[seat[i]] = 0;
                tell_object(pl[seat[i]], table_str(seat[i])); 
        }
        after_winner(PIG_D->card_cmp4(roundcards, SUIT(roundcards[round_order[0]])));
        after_hand();
}

void after_hand()
{
        // doing the scoring here
        int i;
        string collect_all = "";

        for (i = 0; i < 4; i++) {
                hscore[seat[i]] = PIG_D->count_score(picks[seat[i]], bid_flag);
                if (hscore[seat[i]] == 1000)
                        collect_all = seat[i];
                addn("pig_played", 1, pl[seat[i]]);
                addn("pig_score", hscore[seat[i]], pl[seat[i]]);
        }
        if (collect_all == "")
                for (i = 0; i < 4; i++) {
                        tscore[seat[i]] += hscore[seat[i]];
                        if (tscore[seat[i]] <= -1000) 
                                addn("pig_head", 1, pl[seat[i]]);
                }
        else {
                for (i = 0; i < 4; i++)
                        if (seat[i] != collect_all) 
                                addn("pig_head", 1, pl[seat[i]]);
        }
        for (i = 0; i < 4; i++) 
                if (tscore[seat[i]] <= -1000)
                        message_vision("$N是一頭豬！\n", pl[seat[i]]);
        for (i = 0; i < 4; i++)
                if (tscore[seat[i]] <= -1000) {
                        score_reset();
                        break;
                }
        deal_init();
}
        
int do_play(string arg)
{
        object me = this_player();
        int i, c, sc, nbc = 0, cpos = -1;
        string ms;

        if( !(ms=query_temp("pigging_seat", me)) )
                return notify_fail("你沒有在拱豬！\n");
        if (pig_stage != PIG_PLAYING)
                return notify_fail("現在不是出牌階段！\n");
        if (ms != round_order[roundcard_count])
                return notify_fail("還沒輪到你出牌！\n");
        if (!arg || (c = PIG_D->is_validcard(arg)) == -1)
                return notify_fail("你要出哪張牌？\n");
        for (i = 0; i < card_count[ms]; i++) 
                if (cards[ms][i] == c) {
                        cpos = i; break;
                }
        if (cpos == -1)
                return notify_fail("你手裏沒有這張牌！\n");

        if (roundcard_count > 0 && (sc = PIG_D->has_suit(cards[ms], 0, 
                card_count[ms] - 1, SUIT(roundcards[round_order[0]]))) > 0 && 
                SUIT(c) != SUIT(roundcards[round_order[0]]))
                return notify_fail("你不能出這張牌！\n");

        if (roundcard_count == 0 || sc > 1) {
                switch (c) {
                case SPIG :
                        if (!allow_playbid[SPADE])
                                nbc = 1;
                        break;
                case HACE :
                        if (!allow_playbid[HEART])
                                nbc = 1;
                        break;
                case DSHEEP : 
                        if (!allow_playbid[DIAMOND])
                                nbc = 1;
                        break;
                case CTRANS :
                        if (!allow_playbid[CLUB])
                                nbc = 1;
                        break;
                }
                if (nbc)
                        return notify_fail("賣過的牌不能在第一輪出！\n");
        }
        for (i = cpos; i < card_count[ms] - 1; i++)
                cards[ms][i] = cards[ms][i+1];
        cards[ms][13 - round_no] = 53;
        roundcards[ms] = c;
        card_count[ms]--;
        if (roundcard_count > 0 && SUIT(c) != SUIT(roundcards[round_order[0]]))
                message_vision("$N墊了一張" + PIG_D->card_str(c) + "！\n", me);
        else
                message_vision("$N出了一張" + PIG_D->card_str(c) + "！\n", me);
        after_play();
        return 1;
}
