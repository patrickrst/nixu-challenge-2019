FILES = 01_introduction.md \
		02_challenges.md \
		challenges_generated.md \
		03_conclusion.md \
		04_references.md \
		metadata.yaml

OUTPUT = build

FLAGS = -s \
		--pdf-engine=pdflatex \
		--from markdown-raw_tex \
		--template template.latex \
		--listings \
		--bibliography=bibliography.bib \
		--csl=bibliography.csl \
		--metadata link-citations

all: chals pdf

chals:
	find ./../nixu-challenge-2019/ -type f -name 'README.md' -print0 | sort -z | xargs -r0 -I{} sed -e '2,/## Write-up/d' {} | pandoc -s -f markdown-raw_tex -o challenges_generated.md

pdf:
	pandoc $(FLAGS) $(FILES) -o $(OUTPUT)/report.pdf

clean:
	rm $(OUTPUT)/*
