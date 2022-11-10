target/release/day01:
	@cargo build --release

bin.size: target/release/day01
	@strip $<
	@upx --best --lzma $<
	@cat $< | wc -c > $@
