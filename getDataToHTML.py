import re
import markdown
from markdown.extensions import Extension
from markdown.preprocessors import Preprocessor


class CustomSectionExtension(Extension):
    def extendMarkdown(self, md):
        md.preprocessors.register(CustomSectionPreprocessor(md), 'custom_section', 175)


class CustomSectionPreprocessor(Preprocessor):
    def run(self, lines):
        new_lines = []
        in_section = False
        header_content = None
        for line in lines:
            header_match = re.match(r'^\s*#{1,6}\s+(.*)', line)
            if header_match:
                if in_section:
                    new_lines.append('</div>')  # Close the previous section
                    new_lines.append('</section>')  # Close the previous section
                header_content = header_match.group(1).strip()
                header_id = header_content.lower().replace(' ', '-')
                new_lines.append(f'<section id="{header_id}">')
                new_lines.append('<div class="section">')
                new_lines.append(f'<h2>{header_content}</h2>')
                in_section = True
            elif in_section:
                if line.strip() == "":
                    continue  # Skip empty lines
                if line.strip().startswith("!["):
                    # Extracting image source and alt text
                    img_src_match = re.search(r'\((.*?)\)', line)
                    if img_src_match:
                        img_src = img_src_match.group(1)
                        alt_text_match = re.search(r'\[(.*?)\]', line)
                        alt_text = alt_text_match.group(1) if alt_text_match else ""
                        new_lines.append(f'<img src="{img_src}" alt="{alt_text}">')
                elif line.strip().startswith("["):
                    # Extracting link text and URL
                    link_text_match = re.search(r'\[(.*?)\]', line)
                    link_text = link_text_match.group(1) if link_text_match else ""
                    link_url_match = re.search(r'\((.*?)\)', line)
                    link_url = link_url_match.group(1) if link_url_match else ""
                    new_lines.append(f'<a href="{link_url}">{link_text}</a><br>')
                elif line.strip().startswith("```"):
                    new_lines.append(line)  # Preserve code blocks
                else:
                    new_lines.append(f'<p>{line.strip()}</p>')
        if in_section:
            new_lines.append('</div>')  # Close the last section
            new_lines.append('</section>')  # Close the last section
        return new_lines


def markdown_to_html(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as f:
        text = f.read()
        md = markdown.Markdown(extensions=[CustomSectionExtension(), 'markdown.extensions.attr_list'])
        html = md.convert(text)
        with open(output_file, 'w', encoding='utf-8') as out:
            out.write(html)
            
if __name__ == "__main__":
  #  input_file = input("Enter input Markdown file path: ")
  #  output_file = input("Enter output HTML file path: ")
    markdown_to_html("README.md", "output.html")
