target/release/day02:
	@cargo build --release

bin.size: target/release/day02
	@strip $<
	@upx --best --lzma $<
	@cat $< | wc -c > $@
