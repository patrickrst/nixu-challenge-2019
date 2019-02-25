FILES = 01_introduction.md \
		02_challenges.md \
		challenges_generated.md \
		03_conclusion.md \
		metadata.yaml

OUTPUT = build

FLAGS = -s \
		-f markdown \
		--template=template.latex

all: chals pdf

chals:
	find ./../nixu-challenge-2019/ -type f -name 'README.md' -print0 | sort -z | xargs -r0 -I{} sed -e '2,/## Write-up/d' {} | pandoc -s -f markdown -o challenges_generated.md

pdf:
	pandoc $(FLAGS) $(FILES) -o $(OUTPUT)/report.pdf

clean:
	rm build/*
