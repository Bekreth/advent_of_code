target/release/day03:
	@cargo build --release

bin.size: target/release/day03
	@strip $<
	@upx --best --lzma $<
	@cat $< | wc -c > $@
