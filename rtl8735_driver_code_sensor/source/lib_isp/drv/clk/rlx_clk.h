#ifndef _RLX_CLK_H_
#define _RLX_CLK_H_

struct clk_rlx;

struct clk_ops {
	int		(*enable)(struct clk_rlx *clk);
	void	(*disable)(struct clk_rlx *clk);
	int		(*is_enabled)(struct clk_rlx *clk);
	unsigned long	(*recalc_rate)(struct clk_rlx *clk,
					unsigned long parent_rate);
	long		(*round_rate)(struct clk_rlx *clk, unsigned long rate,
					unsigned long *parent_rate);
	int		(*set_parent)(struct clk_rlx *clk, u8 index);
	u8		(*get_parent)(struct clk_rlx *clk);
	int		(*set_rate)(struct clk_rlx *clk, unsigned long rate,
				    unsigned long parent_rate);
};

struct clk_rlx {
	//struct clk_hw hw;
	//from struct clk_init_data
	const char		*name;
	const struct clk_ops	*ops;
	const char * const *parent_names;
	u8	num_parents;
	//from struct clk_init_data

	int num_siblins;
	struct clk_rlx *siblins[8];

	struct clk_rlx *parent;
	u32 clkreg;
	u32 clk_change;
	u32 rate;
	u32 flags;
	u32 mult;
	u32 div;
	u32 *reg_v;
	int reg_i;
};

u32 clk_get_rate(struct clk_rlx *clk);
void clk_set_rate(struct clk_rlx *clk, u32 rate);
long clk_round_rate(struct clk_rlx *clk, u32 rate);
void clk_prepare_enable(struct clk_rlx *clk);
void clk_disable_unprepare(struct clk_rlx *clk);
void clk_put(struct clk_rlx *clk);
struct clk_rlx *clk_get(const char *con_id);
void rlx_clk_init(void);
void rlx_clk_init0(void);

#endif   /* _RLX_CLK_H_ */
